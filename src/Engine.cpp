#include "Engine.h"

Engine::Engine()
{

}

bool Engine::Init(std::string title, int w, int h)
{
	bFullScreen = false;
	
	// Construct renderer
	m_renderer = std::make_unique<Renderer>(title, w, h);

	// Construct input and set callback function
	m_input = std::make_unique<Input>();
	m_input->GLFW_SetKeyboardCallback(m_renderer->GetWindow());
	m_input->GLFW_SetMouseCursorCallback(m_renderer->GetWindow());
	m_input->GLFW_SetMouseButtonCallback(m_renderer->GetWindow());
	m_input->GLFW_SetMouseScrollCallBack(m_renderer->GetWindow());

	// Initialize timing
	m_t1 = std::chrono::system_clock::now();
	m_t2 = std::chrono::system_clock::now();
	nLastFPS = 0;
	fFrameTimer = 1.0f;
	nFrameCount = 0;
	fAccumulator = 0.0f;
	fDeltaTime = 1.0f / 60.0f;

	m_bRunning = true;

	return true;
}

bool Engine::Start()
{
	while (!m_renderer->ShouldClose())
	{
		// Handle timing
		m_t2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = m_t2 - m_t1;
		m_t1 = m_t2;

		// elapsed time
		float fElapsedTime = elapsedTime.count();

		fAccumulator += fDeltaTime;
		// Update Game Logic
		while (fAccumulator >= fDeltaTime)
		{
			ProcessInput();
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

bool Engine::ShutDown()
{
	return true;
}

void Engine::ProcessInput()
{
	m_input->HandleEvent();
	if (m_input->GetKey(Key::ESCAPE).pressed)
	{
		m_renderer->Close();
		//m_bRunning = false;
	}
	if (m_input->GetMouse(0).pressed)
	{
		std::cout << "Mouse Pressed\n";

	}
	if (m_input->GetMouse(0).released)
	{
		std::cout << "Mouse Released\n";
	}

	//std::cout << "Mouse Pos " << m_input->GetMousePos().x << "," << m_input->GetMousePos().y << "\n";
	//std::cout << "Mouse Pos Delta" << m_input->GetMouseDelta().x << "," << m_input->GetMouseDelta().y << "\n";

	if (m_input->GetMouseWheel() > 0)
		std::cout << "Mouse Wheel up " << m_input->GetMouseWheel() << "\n";
	else if (m_input->GetMouseWheel() < 0)
		std::cout << "Mouse Wheel down " << m_input->GetMouseWheel() << "\n";
}

void Engine::Update(float fElapsedTime)
{
	// Game Logic
}

void Engine::Render()
{
	m_renderer->ClearBuffer();
	
	// Draw

	m_renderer->PrepareDrawing();
	m_renderer->DisplayFrame();
}
