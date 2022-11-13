#include "Engine.h"

Engine::Engine()
{

}

bool Engine::Init(std::string title, int w, int h, bool fullscreen, bool vsync)
{
	// Construct window
	m_window = std::make_shared<Window>(title, w, h, fullscreen, vsync);

	// Construct input and set callback functions
	m_input = std::make_shared<Input>();
	m_window->GLFW_SetInputCallback(m_input);

	// Initialize timing
	m_t1 = std::chrono::system_clock::now();
	m_t2 = std::chrono::system_clock::now();
	nLastFPS = 0;
	fFrameTimer = 1.0f;
	nFrameCount = 0;
	fAccumulator = 0.0f;
	fDeltaTime = 1.0f / 60.0f;
	fLastElapsedTime = 0.0f;

	m_bRunning = true;

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
		f32 fElapsedTime = elapsedTime.count();
		fLastElapsedTime = fElapsedTime;

		// Update Game Logic
		fAccumulator += fDeltaTime;
		while (fAccumulator >= fDeltaTime)
		{
			ProcessInput(fElapsedTime);
			Update(fElapsedTime);
			fAccumulator -= fDeltaTime;
		}

		// Render
		Render();

		// FPS
		fFrameTimer += fElapsedTime;
		nFrameCount++;
		if (fFrameTimer >= 1.0f)
		{
			nLastFPS = nFrameCount;
			fFrameTimer -= 1.0f;
			std::cout << "Frame Time: " + std::to_string(fElapsedTime) + " FPS: " + std::to_string(nFrameCount) + "\n";
			nFrameCount = 0;
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
	if (m_input->GetKey(Key::K1).pressed) m_window->SetRenderMode(RenderMode::NORMAL);
	if (m_input->GetKey(Key::K2).pressed) m_window->SetRenderMode(RenderMode::WIREFRAME);

	// Camera Key Control
	if (m_input->GetKey(Key::F1).pressed) m_camera->SetCameraMode(CameraMode::PERSPECTIVE);
	if (m_input->GetKey(Key::F2).pressed) m_camera->SetCameraMode(CameraMode::ORTHOGRAPHIC);
	if (m_input->GetKey(Key::W).held) m_camera->KeyControl(Direction::FORWARD, fElapsedTime);
	if (m_input->GetKey(Key::S).held) m_camera->KeyControl(Direction::BACKWARD, fElapsedTime);
	if (m_input->GetKey(Key::A).held) m_camera->KeyControl(Direction::LEFT, fElapsedTime);
	if (m_input->GetKey(Key::D).held) m_camera->KeyControl(Direction::RIGHT, fElapsedTime);
	if (m_input->GetKey(Key::Q).held) m_camera->KeyControl(Direction::DOWN, fElapsedTime);
	if (m_input->GetKey(Key::E).held) m_camera->KeyControl(Direction::UP, fElapsedTime);

	// Camera Mouse Control
	m_camera->MouseControl(m_input->GetMousePos());
	m_camera->MouseScrollControl(m_input->GetMouseWheel());

	// DEBUG
	// if (m_input->GetMouse(0).pressed) std::cout << "Mouse Pressed\n";
	// if (m_input->GetMouse(0).released) std::cout << "Mouse Released\n";
	//std::cout << "Mouse Pos " << m_input->GetMousePos().x << "," << m_input->GetMousePos().y << "\n";
	//std::cout << "Mouse Pos Delta" << m_input->GetMouseDelta().x << "," << m_input->GetMouseDelta().y << "\n";

	// Change Scene
	if (m_input->GetKey(Key::NP1).pressed)
	{
		m_scene_state->TransitionTo("sandbox");
		std::cout << "Sandbox" << std::endl;
	}
	if (m_input->GetKey(Key::NP2).pressed)
	{
		m_scene_state->TransitionTo("cube_scene");
		std::cout << "cube_scene" << std::endl;
	}

	m_scene_state->ProcessInput(fElapsedTime);
}	

void Engine::Update(f32 fElapsedTime)
{
	m_scene_state->Update(fElapsedTime);
}

void Engine::Render()
{
	m_window->ClearBuffer({10, 10, 10});

	m_scene_state->Render();

	m_window->PrepareDrawing();
	m_window->DisplayFrame();
}