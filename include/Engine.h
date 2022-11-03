#pragma once

#include <iostream>
#include <chrono>
#include <memory>


#include "Window.h"
#include "Input.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"

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
    std::shared_ptr<Model> m_model;
	std::vector<std::shared_ptr<Model>> m_models;

	mf4x4 view;
	mf4x4 projection;
	f32 acc_timer;

	vf3 m_camera_position;
	vf3 m_camera_velocity;
};