#include "Engine.h"

Engine::Engine()
{

}

bool Engine::Init(std::string title, int w, int h, bool fullscreen, bool vsync)
{
	// Construct window
	m_window = std::make_shared<Window>(title, w, h, fullscreen, vsync);

	// Construct input
	m_input = std::make_shared<Input>();

	// Initialize timing
	m_t1 = std::chrono::system_clock::now();
	m_t2 = std::chrono::system_clock::now();
	m_last_fps = 0;
	m_frame_timer = 1.0f;
	m_frame_count = 0;
	m_accumulator = 0.0f;
	m_delta_time = 1.0f / 60.0f;
	m_last_elapsed_time = 0.0f;

	m_running = true;

	// Create Camera
	m_camera = std::make_shared<Camera>(vf3{ 0.0f, 0.0f, 3.0f });

	// Create Scene State Machine
	m_scene_state = std::make_unique<SceneStateMachine>();

	// Create Scene
	std::shared_ptr<Scene> sandbox = std::make_shared<Sandbox>(m_window, m_input, m_camera);
	m_scene_state->Add("sandbox", sandbox);

	std::shared_ptr<Scene> cube_scene = std::make_shared<CubeScene>(m_window, m_input, m_camera);
	m_scene_state->Add("cube_scene", cube_scene);

	// Set Active Scene
	m_scene_state->TransitionTo("sandbox");

	return true;
}

bool Engine::Start()
{
	while (!m_window->ShouldClose())
	{
		// Handle timing
		m_t2 = std::chrono::system_clock::now();
		std::chrono::duration<f32> elapsedTime = m_t2 - m_t1;
		m_t1 = m_t2;

		// Elapsed time
		f32 m_elapsed_time = elapsedTime.count();
		m_last_elapsed_time = m_elapsed_time;

		// Update Game Logic
		m_accumulator += m_delta_time;
		while (m_accumulator >= m_delta_time)
		{
			ProcessInput(m_elapsed_time);
			Update(m_elapsed_time);
			m_accumulator -= m_delta_time;
		}

		// Render
		Render();

		// FPS
		m_frame_timer += m_elapsed_time;
		m_frame_count++;
		if (m_frame_timer >= 1.0f)
		{
			m_last_fps = m_frame_count;
			m_frame_timer -= 1.0f;
			std::cout << "Frame Time: " + std::to_string(m_elapsed_time) + " FPS: " + std::to_string(m_frame_count) + "\n";
			m_frame_count = 0;
		}
	}

	return true;
}

bool Engine::Shutdown()
{
	return true;
}

void Engine::ProcessInput(f32 fElapsedTime)
{
	m_input->HandleEvent();

	// Application Control
	if (m_input->GetKey(Key::ESCAPE).pressed) m_window->Close();
	if (m_input->GetKey(Key::TAB).pressed) m_window->ToggleMouseFocus();
	if (m_input->GetKey(Key::F11).pressed) m_window->ToggleFullScreen();
	
	// Rendering Mode Control
	if (m_input->GetKey(Key::K1).pressed) m_window->SetRenderMode(RenderMode::NORMAL);
	if (m_input->GetKey(Key::K2).pressed) m_window->SetRenderMode(RenderMode::WIREFRAME);

	// Camera Mode Control
	if (m_input->GetKey(Key::F1).pressed) m_camera->SetMode(CameraMode::PERSPECTIVE);
	if (m_input->GetKey(Key::F2).pressed) m_camera->SetMode(CameraMode::ORTHOGRAPHIC);
	if (m_input->GetKey(Key::F3).pressed) m_camera->SetMode(CameraMode::ORBIT);

	// Camera Key Control
	if (m_camera->GetMode() == CameraMode::PERSPECTIVE)
	{
		if (m_input->GetKey(Key::W).held) m_camera->KeyControl(Direction::FORWARD, fElapsedTime);
		if (m_input->GetKey(Key::S).held) m_camera->KeyControl(Direction::BACKWARD, fElapsedTime);
		if (m_input->GetKey(Key::A).held) m_camera->KeyControl(Direction::LEFT, fElapsedTime);
		if (m_input->GetKey(Key::D).held) m_camera->KeyControl(Direction::RIGHT, fElapsedTime);
		if (m_input->GetKey(Key::Q).held) m_camera->KeyControl(Direction::DOWN, fElapsedTime);
		if (m_input->GetKey(Key::E).held) m_camera->KeyControl(Direction::UP, fElapsedTime);

		m_camera->MouseControl(m_input->GetMousePos());
		m_camera->MousePanControl(m_input->GetMousePos());
	}
	// TODO Make Orbit Camera Control More Intuitive
	else if (m_camera->GetMode() == CameraMode::ORBIT)
	{
		if (m_input->GetMouse(0).held)
			m_camera->MouseOrbitControl(m_input->GetMousePos()); // Jumping position when go back to perspective; store position?
		if (m_input->GetMouse(1).held)
			m_camera->MousePanControl(m_input->GetMousePos());
	}
	else if (m_camera->GetMode() == CameraMode::ORTHOGRAPHIC)
	{
		if (m_input->GetMouse(0).held)
			m_camera->MouseOrbitControl(m_input->GetMousePos());
		if (m_input->GetMouse(1).held)
			m_camera->MousePanControl(m_input->GetMousePos());
	}

	// Camera Mouse Control
	m_camera->MouseScrollControl(m_input->GetMouseWheel());

	// DEBUG
	//std::cout << "Mouse Pos " << m_input->GetMousePos().x << "," << m_input->GetMousePos().y << "\n";
	//std::cout << "Mouse Pos Delta " << m_input->GetMouseDelta().x << "," << m_input->GetMouseDelta().y << "\n";
	//std::cout << "Camera Pos " << m_camera->GetPosition().x << "," << m_camera->GetPosition().y << "," << m_camera->GetPosition().z << "\n";

	// Scene Control
	if (m_input->GetKey(Key::NP1).pressed)
	{
		m_scene_state->TransitionTo("sandbox");
		std::cout << "Sandbox Scene" << std::endl;
	}
	if (m_input->GetKey(Key::NP2).pressed)
	{
		m_scene_state->TransitionTo("cube_scene");
		std::cout << "Cube Scene" << std::endl;
	}

	m_scene_state->ProcessInput(fElapsedTime);
}	

void Engine::Update(f32 fElapsedTime)
{
	m_scene_state->Update(fElapsedTime);
}

void Engine::Render()
{
	m_window->ClearBuffer({25, 25, 25});

	m_scene_state->Render();

	m_window->PrepareDrawing();
	m_window->DisplayFrame();
}