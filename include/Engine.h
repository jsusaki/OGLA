#pragma once

#include <iostream>
#include <chrono>
#include <memory>

#include "Window.h"
#include "Input.h"
#include "Shader.h"
#include "Vertex.h"
#include "VertexData.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"


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
	u32 nLastFPS;
	u32 nFrameCount;
	f32 fFrameTimer;
	f32 fAccumulator;
	f32 fDeltaTime;

	// Tests
	std::unique_ptr<VertexBuffer> vbo;
	std::unique_ptr<IndexBuffer> ibo;
	std::unique_ptr<VertexArray> vao;
	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<Texture> m_texture1;
	std::unique_ptr<Texture> m_texture2;
};