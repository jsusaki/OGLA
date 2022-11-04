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
	fLastElapsedTime = 0.0f;

	m_bRunning = true;

	/*
	// Create Quad
	std::vector<Vertex> vertices = {
		{{ 0.5f, 0.5f, 0.0f },{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}},   // top right
		{{ 0.5f,-0.5f, 0.0f },{ 1.0f, 0.0f },{0.0f, 1.0f, 0.0f}},   // bottom right
		{{-0.5f,-0.5f, 0.0f },{ 0.0f, 0.0f },{0.0f, 0.0f, 1.0f}},   // bottom left
		{{-0.5f, 0.5f, 0.0f },{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}},   // top left
	};
	std::vector<u32> indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	*/

	// Unit cube      
	// A cube has 6 sides and each side has 4 vertices, therefore, the total number
	// of vertices is 24 (6 sides * 4 verts), and 72 floats in the vertex array
	// since each vertex has 3 components (x,y,z) (= 24 * 3)
	//    v6----- v5  
	//   /|      /|   
	//  v1------v0|   
	//  | |     | |   
	//  | v7----|-v4  
	//  |/      |/    
	//  v2------v3   

	// Create Cube Vertices
	std::vector<Vertex> vertices = {
		// Front
		{{ 0.5f, 0.5f, 0.5f},{ 1.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v0
		{{-0.5f, 0.5f, 0.5f},{ 0.0f, 0.0f },{0.0f, 1.0f, 0.0f}}, //v1
		{{-0.5f,-0.5f, 0.5f},{ 0.0f, 1.0f },{0.0f, 0.0f, 1.0f}}, //v2
		{{ 0.5f,-0.5f, 0.5f},{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v3
		// Right
		{{ 0.5f, 0.5f, 0.5f},{ 0.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v0
		{{ 0.5f,-0.5f, 0.5f},{ 0.0f, 1.0f },{0.0f, 1.0f, 0.0f}}, //v3
		{{ 0.5f,-0.5f,-0.5f},{ 1.0f, 1.0f },{0.0f, 0.0f, 1.0f}}, //v4
		{{ 0.5f, 0.5f,-0.5f},{ 1.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v5
		// Top
		{{ 0.5f, 0.5f, 0.5f},{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v0   
		{{ 0.5f, 0.5f,-0.5f},{ 1.0f, 0.0f },{0.0f, 1.0f, 0.0f}}, //v5
		{{-0.5f, 0.5f,-0.5f},{ 0.0f, 0.0f },{0.0f, 0.0f, 1.0f}}, //v6
		{{-0.5f, 0.5f, 0.5f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v1
		// Left
		{{-0.5f, 0.5f, 0.5f},{ 1.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v1  
		{{-0.5f, 0.5f,-0.5f},{ 0.0f, 0.0f },{0.0f, 1.0f, 0.0f}}, //v6
		{{-0.5f,-0.5f,-0.5f},{ 0.0f, 1.0f },{0.0f, 0.0f, 1.0f}}, //v7
		{{-0.5f,-0.5f, 0.5f},{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v2
		// Bottom
		{{-0.5f,-0.5f,-0.5f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v7 
		{{ 0.5f,-0.5f,-0.5f},{ 1.0f, 1.0f },{0.0f, 1.0f, 0.0f}}, //v4
		{{ 0.5f,-0.5f, 0.5f},{ 1.0f, 0.0f },{0.0f, 0.0f, 1.0f}}, //v3
		{{-0.5f,-0.5f, 0.5f},{ 0.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v2
		// Back
 		{{ 0.5f,-0.5f,-0.5f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v4 
		{{-0.5f,-0.5f,-0.5f},{ 1.0f, 1.0f },{0.0f, 1.0f, 0.0f}}, //v7
		{{-0.5f, 0.5f,-0.5f},{ 1.0f, 0.0f },{0.0f, 0.0f, 1.0f}}, //v6
		{{ 0.5f, 0.5f,-0.5f},{ 0.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v5
	};
	// Create Cube Indices
	std::vector<u32> indices = {
		// Front
		0, 1, 2,  //v0-v1-v2 
		2, 3, 0,  //v2-v3-v0 
		// right
		4, 5, 6,  //v0-v3-v4 
		6, 7, 4,  //v4-v5-v0 
		// top
		8, 9, 10, //v0-v5-v6,   
		10,11, 8, //v6-v1-v0
		// left
		12,13,14, //v1-v6-v7 
		14,15,12, //v7-v2-v1
		// bottom
		16,17,18, //v7-v4-v3
		18,19,16, //v3-v2-v7
		// back
		20,21,22, //v4-v7-v6  
		22,23,20  //v6-v5-v4
	};
	// Create Vertex Buffer Definition
	VertexData def;
	def.Add<vf3>(); // position
	def.Add<vf2>(); // texture
	def.Add<vf3>(); // color
	// Create Cube Position
	std::vector<vf3> CubePositions = {
		{ 0.0f, 0.0f, 0.0f },
		{ 2.0f, 5.0f,-15.0f},
		{-1.5f,-2.2f,-2.5f },
		{-3.8f,-2.0f,-12.3f},
		{ 2.4f,-0.4f,-3.5f },
		{-1.7f, 3.0f,-7.5f },
		{ 1.3f,-2.0f,-2.5f },
		{ 1.5f, 2.0f,-2.5f },
		{ 1.5f, 0.2f,-1.5f },
		{-1.3f, 1.0f,-1.5f },

		{ 5.0f, 5.0f,  5.0f },
		{ 6.0f, 7.0f,-25.0f },
		{-5.5f,-6.2f,-12.5f },
		{-7.8f,-6.0f,-22.3f },
		{ 6.4f,-5.4f,-13.5f },
		{-6.7f, 7.0f,-17.5f },
		{ 6.3f,-6.0f,-12.5f },
		{ 6.5f, 6.0f,-12.5f },
		{ 6.5f, 5.2f,-11.5f },
		{-6.3f, 6.0f,-11.5f }
	};
	// Create Shader
	m_shader = std::make_shared<Shader>("../../res/shaders/shader.vs", "../../res/shaders/shader.fs");
	// Create Texture
	m_texture1 = std::make_shared<Texture>("../../res/textures/lisp.jpg", true);
	// Create Models
	for (u32 i = 0; i < CubePositions.size(); i++)
	{
		m_model = std::make_shared<Model>(vertices, indices, def);
		// Add Texture: how to associate texture with model?
		m_model->m_textures.push_back(m_texture1);
		// Set Model Positions
		m_model->Translate(CubePositions[i]);
		// Add Model to Models
		m_models.push_back(m_model);
	}
	// Set Texture
	m_shader->Use();
	m_shader->SetUniform("texture1", 0);

	// Create Camera
	m_camera = std::make_unique<Camera>(vf3{ 0.0f, 0.0f, 3.0f });

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
		fLastElapsedTime = fElapsedTime;

		// Update Game Logic
		fAccumulator += fDeltaTime;
		while (fAccumulator >= fDeltaTime)
		{
			ProcessInput(fElapsedTime);
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

void Engine::ProcessInput(f32 fElapsedTime)
{
	m_input->HandleEvent();

	// Application Control
	if (m_input->GetKey(Key::ESCAPE).pressed) m_window->Close();
	if (m_input->GetKey(Key::TAB).pressed) m_window->ToggleMouseFocus();
	if (m_input->GetKey(Key::F11).pressed) m_window->ToggleFullScreen();

	// Camera Key Control
	if (m_input->GetKey(Key::W).held) m_camera->KeyControl(Direction::FORWARD, fElapsedTime);
	if (m_input->GetKey(Key::S).held) m_camera->KeyControl(Direction::BACKWARD, fElapsedTime);
	if (m_input->GetKey(Key::A).held) m_camera->KeyControl(Direction::LEFT, fElapsedTime);
	if (m_input->GetKey(Key::D).held) m_camera->KeyControl(Direction::RIGHT, fElapsedTime);
	if (m_input->GetKey(Key::Q).held) m_camera->KeyControl(Direction::DOWN, fElapsedTime);
	if (m_input->GetKey(Key::E).held) m_camera->KeyControl(Direction::UP, fElapsedTime);
	
	// Camera Mouse Control
	m_camera->MouseControl(m_input->GetMousePos());

	// if (m_input->GetMouse(0).pressed) std::cout << "Mouse Pressed\n";
	// if (m_input->GetMouse(0).released) std::cout << "Mouse Released\n";
	//std::cout << "Mouse Pos " << m_input->GetMousePos().x << "," << m_input->GetMousePos().y << "\n";
	//std::cout << "Mouse Pos Delta" << m_input->GetMouseDelta().x << "," << m_input->GetMouseDelta().y << "\n";
}	

void Engine::Update(f32 fElapsedTime)
{
	// Game Logic
	acc_timer += fElapsedTime * 3;

	// Model transformations
	for (u32 i = 0; i < m_models.size(); i++)
		m_models[i]->Rotate(acc_timer * i, { 1.0f, 0.3f, 0.5f });
}

void Engine::Render()
{
	m_window->ClearBuffer();

	// Draw ===================================================================

	// Set View and Projection Matrix
	m_shader->SetUniform("view", m_camera->GetViewMatrix());
	m_shader->SetUniform("projection", m_camera->GetProjectionMatrix((f32)m_window->Width() / (f32)m_window->Height()));

	// Draw Models
	for (auto& m : m_models) m->Draw(m_shader);

	// ========================================================================

	m_window->PrepareDrawing();
	m_window->DisplayFrame();
}
