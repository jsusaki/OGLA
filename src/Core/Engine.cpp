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

	// Create Scene State Machine
	m_scene_state = std::make_unique<SceneStateMachine>();

	// Override
	OnCreate();

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
			std::println("Frame Time: {} FPS: {}", m_elapsed_time, m_frame_count);
			m_frame_count = 0;
		}
	}

	return true;
}

bool Engine::Shutdown()
{
	return true;
}

void Engine::ProcessInput(f32 elapsed_time)
{
	m_input->HandleEvent();
	m_scene_state->ProcessInput(elapsed_time);
}	

void Engine::Update(f32 elapsed_time)
{
	OnUpdate(elapsed_time);
	m_scene_state->Update(elapsed_time);
}

void Engine::Render()
{
	m_window->ClearBuffer({25, 25, 25});

	m_scene_state->Render();

	m_window->PrepareDrawing();
	m_window->DisplayFrame();
}