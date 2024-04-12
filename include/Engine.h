#pragma once

#include <iostream>
#include <chrono>
#include <memory>

#include "Window.h"
#include "Input.h"
#include "SceneStateMachine.h"


class Engine
{
public:
	Engine();

public:
	bool Init(std::string title, int w, int h, bool fullscreen = false, bool vsync = false);
	bool Start();
	bool Shutdown();

public:
	void ProcessInput(f32 fElapsedTime);
	void Update(f32 fElapsedTime);
	void Render();

private:
	bool m_running;

	// Core systems
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Input> m_input;
	std::shared_ptr<Camera> m_camera;
	std::unique_ptr<SceneStateMachine> m_scene_state;

	// Frame time handling
	std::chrono::time_point<std::chrono::system_clock> m_t1;
	std::chrono::time_point<std::chrono::system_clock> m_t2;
	u32 m_last_fps;
	u32 m_frame_count;
	f32 m_frame_timer;
	f32 m_accumulator;
	f32 m_delta_time;
	f32 m_last_elapsed_time;
};