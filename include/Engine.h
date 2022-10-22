#pragma once
#include <iostream>
#include <chrono>
#include <memory>

#include "Renderer.h"
#include "Input.h"

class Engine
{
public:
	Engine();

public:
	bool Init(std::string title, int w, int h, bool fullscreen = false, bool vsync = false);
	bool Start();
	bool ShutDown();

public:
	void ProcessInput();
	void Update(float fElapsedTime);
	void Render();

private:
	bool m_bRunning;
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;

	std::chrono::time_point<std::chrono::system_clock> m_t1;
	std::chrono::time_point<std::chrono::system_clock> m_t2;
	uint32_t nLastFPS;
	int nFrameCount;
	float fFrameTimer;
	float fAccumulator;
	float fDeltaTime;
};