#pragma once
#include <iostream>
#include <chrono>
#include <memory>

#include "Window.h"
#include "Input.h"

class Engine
{
public:
	Engine();

public:
	bool Init(std::string title, int w, int h, bool fullscreen = false, bool vsync = false);
	bool Start();
	bool Shutdown();

public:
	void ProcessInput();
	void Update(float fElapsedTime);
	void Render();

private:
	bool m_bRunning;
	std::unique_ptr<Window> m_window;
	std::unique_ptr<Input> m_input;

	std::chrono::time_point<std::chrono::system_clock> m_t1;
	std::chrono::time_point<std::chrono::system_clock> m_t2;
	uint32_t nLastFPS;
	int nFrameCount;
	float fFrameTimer;
	float fAccumulator;
	float fDeltaTime;
};