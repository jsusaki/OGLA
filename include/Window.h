#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Type.h"
#include "Input.h"


class Window
{
public:
	Window(std::string title, int w, int h, bool fullscreen, bool vsync);
	~Window();

public:
	void Create(std::string title, int w, int h, bool fullscreen, bool vsync);
	void Close();

public:
	void UpdateViewport(const vi2& m_pos, const vi2& m_size);
	void ClearBuffer(pixel p = { 0, 0, 0 }, bool depth = true);
	void PrepareDrawing(bool depth = true, bool cullface = false);
	void DisplayFrame();

public:
	int Width();
	int Height();
	GLFWwindow* GetWindow();
	bool ShouldClose();
	void ToggleFullScreen();
	void ToggleVsync();

public:
	void GetPrimaryMonitor();
	void SetVsync(bool vsync);
	bool IsVsync();
	void SetFullScreen(bool fullscreen);
	bool IsFullScreen();

private:
	// Internal Configurations
	void GLFW_Init();
	void GLFW_CreateWindow(std::string title, int w, int h, bool fullscreen, bool vsync);
	void GLAD_Load();
	void GLFW_SetFrameBufferSizeCallback();

private:
	GLFWwindow* m_window;
	GLFWmonitor* m_monitor;

	struct param
	{
		std::string m_title;
		vi2 m_pos;
		vi2 m_size;
		bool m_fullscreen;
		bool m_vsync;
	};

	param p;
};