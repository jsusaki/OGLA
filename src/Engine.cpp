#define STB_IMAGE_IMPLEMENTATION

#include "Engine.h"

Engine::Engine()
{

}

bool Engine::Init(std::string title, int w, int h, bool fullscreen, bool vsync)
{
	// Construct window
	m_window = std::make_unique<Window>(title, w, h, fullscreen, vsync);

	// Construct input and set callback function
	m_input = std::make_unique<Input>();
	m_input->GLFW_SetKeyboardCallback(m_window->GetWindow());
	m_input->GLFW_SetMouseCursorCallback(m_window->GetWindow());
	m_input->GLFW_SetMouseButtonCallback(m_window->GetWindow());
	m_input->GLFW_SetMouseScrollCallBack(m_window->GetWindow());

	// Initialize timing
	m_t1 = std::chrono::system_clock::now();
	m_t2 = std::chrono::system_clock::now();
	nLastFPS = 0;
	fFrameTimer = 1.0f;
	nFrameCount = 0;
	fAccumulator = 0.0f;
	fDeltaTime = 1.0f / 60.0f;

	m_bRunning = true;


	// Test Shader
	m_shader = std::make_unique<Shader>("../../res/shaders/shader.vs", "../../res/shaders/shader.fs");
	m_texture1 = std::make_unique<Texture>("../../res/textures/container.jpg");
	m_texture2 = std::make_unique<Texture>("../../res/textures/awesomeface.png");

	// Construct Vertex Data Definition
	VertexData def;
	def.Add<vf3>(); // position
	def.Add<vf4>(); // color
	def.Add<vf2>(); // texture

	// Construct Vertices
	// Rectangle
	std::vector<Vertex> vertices = {
		{{ 0.5f, 0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f, 0.0f },{1.0f, 1.0f}},   // top right
		{{ 0.5f,-0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f, 0.0f },{1.0f, 0.0f}},   // bottom right
		{{-0.5f,-0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f, 0.0f },{0.0f, 0.0f}},   // bottom left
		{{-0.5f, 0.5f, 0.0f },{ 1.0f, 1.0f, 1.0f, 0.0f },{0.0f, 1.0f}},   // top left
	};

	// Construct Indices
	std::vector<u32> indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	vbo = std::make_unique<VertexBuffer>(vertices, STATIC_DRAW);
	ibo = std::make_unique<IndexBuffer>(indices, STATIC_DRAW);
	vao = std::make_unique<VertexArray>();

	// Bind VBO and Vertex Data Definition for Vertex Atrributes
	vao->Bind(*vbo, *ibo, def);

	m_shader->Use();
	m_shader->SetUniform("texture1", 0);
	m_shader->SetUniform("texture2", 1);

	return true;
}

bool Engine::Start()
{
	while (!m_window->ShouldClose())
	{
		// Handle timing
		m_t2 = std::chrono::system_clock::now();
		std::chrono::duration<f32> elapsedTime = m_t2 - m_t1;
		m_t1 = m_t2;

		// Elapsed time
		f32 fElapsedTime = elapsedTime.count();

		// Update Game Logic
		fAccumulator += fDeltaTime;
		while (fAccumulator >= fDeltaTime)
		{
			ProcessInput();
			Update(fElapsedTime);
			fAccumulator -= fDeltaTime;
		}

		// Render
		Render();

		// FPS
		fFrameTimer += fElapsedTime;
		nFrameCount++;
		if (fFrameTimer >= 1.0f)
		{
			nLastFPS = nFrameCount;
			fFrameTimer -= 1.0f;
			std::cout << "Frame Time: " + std::to_string(fElapsedTime) + " FPS: " + std::to_string(nFrameCount) + "\n";
			nFrameCount = 0;
		}
	}

	return true;
}

bool Engine::Shutdown()
{
	return true;
}

void Engine::ProcessInput()
{
	m_input->HandleEvent();

	// Keyboard Input
	if (m_input->GetKey(Key::ESCAPE).pressed)
	{
		m_window->Close();
	}
	if (m_input->GetKey(Key::F11).pressed)
	{	
		m_window->ToggleFullScreen();
	}

	// Mouse Input
	if (m_input->GetMouse(0).pressed)
	{
		//std::cout << "Mouse Pressed\n";
	}
	if (m_input->GetMouse(0).released)
	{
		//std::cout << "Mouse Released\n";
	}
	if (m_input->GetMouseWheel() > 0)
	{
		//std::cout << "Mouse Wheel up " << m_input->GetMouseWheel() << "\n";
	}
	else if (m_input->GetMouseWheel() < 0)
	{
		//std::cout << "Mouse Wheel down " << m_input->GetMouseWheel() << "\n";
	}

	//std::cout << "Mouse Pos " << m_input->GetMousePos().x << "," << m_input->GetMousePos().y << "\n";
	//std::cout << "Mouse Pos Delta" << m_input->GetMouseDelta().x << "," << m_input->GetMouseDelta().y << "\n";
}	

void Engine::Update(float fElapsedTime)
{
	// Game Logic
}

void Engine::Render()
{
	m_window->ClearBuffer();

	// Draw
	// ========================================================================

	// Renderer Functions
	glActiveTexture(GL_TEXTURE0);
	m_texture1->Bind();
	glActiveTexture(GL_TEXTURE1);
	m_texture2->Bind();

	m_shader->Use();
	glBindVertexArray(vao->GetVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// ========================================================================

	m_window->PrepareDrawing();
	m_window->DisplayFrame();
}
