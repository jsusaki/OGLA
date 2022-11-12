#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Type.h"
#include "Input.h"


enum class RenderMode
{
	NORMAL = 0,
	WIREFRAME = 1
};

class Window
{
public:
	Window(std::string title, int w, int h, bool fullscreen, bool vsync);
	~Window();

public:
	void Create(std::string title, int w, int h, bool fullscreen, bool vsync);
	void Close();

public:
	// TODO: Separte into Renderer Class
	void UpdateViewport(const vi2& pos, const vi2& size);
	void ClearBuffer(pixel p = { 0, 0, 0 }, bool depth = true);
	void PrepareDrawing(bool depth = true, bool cullface = false);
	void DisplayFrame();

public:
	s32 Width();
	s32 Height();
	GLFWwindow* GetWindow();
	bool ShouldClose();
	void ToggleFullScreen();
	void SetFullScreen(bool fullscreen);
	bool IsFullScreen();
	void ToggleVsync();
	void SetVsync(bool vsync);
	bool IsVsync();
	void ToggleMouseFocus();
	void SetMouseInputFocus(bool focus);
	bool IsMouseFocused();

public:
	void GetPrimaryMonitor();
	RenderMode GetRenderMode();
	void SetRenderMode(RenderMode mode);

	void GLFW_SetInputCallback(std::shared_ptr<Input> input);
	
private:
	// Internal Configurations
	void GLFW_Init();
	void GLFW_CreateWindow(std::string title, int w, int h, bool fullscreen, bool vsync);
	void GLAD_Load();
	void GLFW_SetFrameBufferSizeCallback();

	void GLFW_SetKeyboardCallback(std::shared_ptr<Input> input);
	void GLFW_SetMouseCursorCallback(std::shared_ptr<Input> input);
	void GLFW_SetMouseButtonCallback(std::shared_ptr<Input> input);
	void GLFW_SetMouseScrollCallBack(std::shared_ptr<Input> input);

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
	} p;

	bool m_mouse_input_focus;

	RenderMode m_render_mode;
};