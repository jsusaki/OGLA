#pragma once
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Input.h"
#include "Common.h"

class Renderer
{
public:
	Renderer(std::string title, int w, int h);
	~Renderer();

public:
	void Create(std::string title, int w, int h);
	void Close();

public:
	void UpdateViewport(const vi2& pos, const vi2& size);
	void ClearBuffer(pixel p = { 0, 0, 0 }, bool depth = true);
	void PrepareDrawing(bool depth = true, bool cullface = false);
	void DisplayFrame();

public:
	int Width();
	int Height();
	GLFWwindow* GetWindow();
	bool ShouldClose();

private:
	// Internal Configurations
	void GLFW_Init();
	void GLFW_CreateWindow(std::string title, int w, int h);
	void GLAD_Load();
	void GLFW_SetFrameBufferSizeCallback();

private:
	GLFWwindow* m_window;
	struct param
	{
		std::string m_title;
		int m_width;
		int m_height;
	};
	param p;
};