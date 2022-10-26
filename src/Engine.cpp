#include "Engine.h"

Engine::Engine()
{

}

bool Engine::Init(std::string title, int w, int h, bool fullscreen, bool vsync)
{
	// Construct renderer
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

	return true;
}

bool Engine::Start()
{
	while (!m_window->ShouldClose())
	{
		// Handle timing
		m_t2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = m_t2 - m_t1;
		m_t1 = m_t2;

		// Elapsed time
		float fElapsedTime = elapsedTime.count();

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

	m_shader->Use();

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	// TODO: Abstract VBO, VAO, EBO, Buffer Layout
	unsigned int VBO, VAO;
	// Generate Vertex Array and Buffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind Vertex Array Object
	glBindVertexArray(VAO);
	// Bind and set Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Configure vertex attributes
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Render Triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// ========================================================================



	m_window->PrepareDrawing();
	m_window->DisplayFrame();
}
