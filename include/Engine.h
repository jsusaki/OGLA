#pragma once

#include <iostream>
#include <chrono>
#include <memory>

#include "Window.h"
#include "Input.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Shape.h"


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
	std::unique_ptr<Window> m_window;
	std::unique_ptr<Input> m_input;

	// Frame time handling
	std::chrono::time_point<std::chrono::system_clock> m_t1;
	std::chrono::time_point<std::chrono::system_clock> m_t2;
	u32 nLastFPS;
	u32 nFrameCount;
	f32 fFrameTimer;
	f32 fAccumulator;
	f32 fDeltaTime;
	f32 fLastElapsedTime;

	// Tests
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture> m_texture1;
	std::vector<std::shared_ptr<Model>> m_models;
	f32 acc_timer;
	std::unique_ptr<Camera> m_camera;
};