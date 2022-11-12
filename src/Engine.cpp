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

	// Create Scene
	m_active_scene = std::make_shared<Sandbox>(m_window, m_input);
	// Initialize Scene
	m_active_scene->Init();

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
	m_active_scene->ProcessInput(fElapsedTime);
}	

void Engine::Update(f32 fElapsedTime)
{
	m_active_scene->Update(fElapsedTime);
}

void Engine::Render()
{
	m_window->ClearBuffer({25, 25, 25});

	m_active_scene->Render();

	m_window->PrepareDrawing();
	m_window->DisplayFrame();
}