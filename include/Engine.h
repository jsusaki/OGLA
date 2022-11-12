#pragma once

#include <iostream>
#include <chrono>
#include <memory>

#include "Window.h"
#include "Input.h"
#include "Scene.h"


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
	bool m_bRunning;

	// Core systems
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Input> m_input;

	// TODO: Add Scene State Machine
	std::shared_ptr<Scene> m_active_scene;
	//std::map<std::string, Scene> m_scenes;

	// Frame time handling
	std::chrono::time_point<std::chrono::system_clock> m_t1;
	std::chrono::time_point<std::chrono::system_clock> m_t2;
	u32 nLastFPS;
	u32 nFrameCount;
	f32 fFrameTimer;
	f32 fAccumulator;
	f32 fDeltaTime;
	f32 fLastElapsedTime;
};