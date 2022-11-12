#include "Scene.h"

Sandbox::Sandbox(std::shared_ptr<Window> window, std::shared_ptr<Input> input) : m_window(std::move(window)), m_input(std::move(input))
{

}

void Sandbox::Init()
{
	// Create Camera
	m_camera = std::make_unique<Camera>(vf3{ 0.0f, 0.0f, 3.0f });

	// Create Cube
	Cube cube;

	// Create Shaders
	m_shaders = {
		{"core", std::make_shared<Shader>("../../res/shaders/core.vs", "../../res/shaders/core.fs")},
		{"cube_light", std::make_shared<Shader>("../../res/shaders/cube_light.vs", "../../res/shaders/cube_light.fs")},
	};

	// Create Textures
	m_textures = {
		{"lisp", std::make_shared<Texture>("../../res/textures/lisp.jpg")},
		{"lisp_meta", std::make_shared<Texture>("../../res/textures/meta-circular-evaluator.jpg")},
	};

	// Create Light
	m_light = std::make_shared<Light>(vf3(1.2f, 1.0f, 2.0f), vf3(0.2f, 0.2f, 0.2f), vf3(0.5f, 0.5f, 0.5f), vf3(1.0f, 1.0f, 1.0f));

	// Create Material
	m_material = std::make_shared<Material>(64.0f, 0, -1, 1);

	// Create Models
	// Create Material Cube
	std::shared_ptr<Model> material_cube = std::make_shared<Model>(cube);
	material_cube->AddTexture(m_textures["lisp"]);
	material_cube->AddTexture(m_textures["lisp_meta"]);
	material_cube->AddMaterial(m_material);
	m_models.push_back(material_cube);
	// Create Light Cube
	std::shared_ptr<Model> light_cube = std::make_shared<Model>(cube);
	light_cube->SetPosition(m_light->m_position);
	light_cube->SetScale({ 0.2f, 0.2f, 0.2f });
	m_models.push_back(light_cube);
}

void Sandbox::ProcessInput(f32 fElapsedTime)
{
	// Application Control
	if (m_input->GetKey(Key::ESCAPE).pressed) m_window->Close();
	if (m_input->GetKey(Key::TAB).pressed) m_window->ToggleMouseFocus();
	if (m_input->GetKey(Key::F11).pressed) m_window->ToggleFullScreen();
	if (m_input->GetKey(Key::K1).pressed) m_window->SetRenderMode(RenderMode::NORMAL);
	if (m_input->GetKey(Key::K2).pressed) m_window->SetRenderMode(RenderMode::WIREFRAME);

	// Camera Key Control
	if (m_input->GetKey(Key::F1).pressed) m_camera->SetCameraMode(CameraMode::PERSPECTIVE);
	if (m_input->GetKey(Key::F2).pressed) m_camera->SetCameraMode(CameraMode::ORTHOGRAPHIC);
	if (m_input->GetKey(Key::W).held) m_camera->KeyControl(Direction::FORWARD, fElapsedTime);
	if (m_input->GetKey(Key::S).held) m_camera->KeyControl(Direction::BACKWARD, fElapsedTime);
	if (m_input->GetKey(Key::A).held) m_camera->KeyControl(Direction::LEFT, fElapsedTime);
	if (m_input->GetKey(Key::D).held) m_camera->KeyControl(Direction::RIGHT, fElapsedTime);
	if (m_input->GetKey(Key::Q).held) m_camera->KeyControl(Direction::DOWN, fElapsedTime);
	if (m_input->GetKey(Key::E).held) m_camera->KeyControl(Direction::UP, fElapsedTime);

	// Camera Mouse Control
	m_camera->MouseControl(m_input->GetMousePos());
	m_camera->MouseScrollControl(m_input->GetMouseWheel());

	// DEBUG
	// if (m_input->GetMouse(0).pressed) std::cout << "Mouse Pressed\n";
	// if (m_input->GetMouse(0).released) std::cout << "Mouse Released\n";
	//std::cout << "Mouse Pos " << m_input->GetMousePos().x << "," << m_input->GetMousePos().y << "\n";
	//std::cout << "Mouse Pos Delta" << m_input->GetMouseDelta().x << "," << m_input->GetMouseDelta().y << "\n";
}

void Sandbox::Update(f32 fElapsedTime)
{
	acc_timer += fElapsedTime;
}

void Sandbox::Render()
{
	// Update Uniforms
	m_light->Use(m_shaders["core"]);

	m_shaders["core"]->SetUniform("viewPos", m_camera->GetPosition());

	// Set View and Projection Matrix
	m_shaders["core"]->SetUniform("view", m_camera->GetViewMatrix());
	m_shaders["core"]->SetUniform("projection", m_camera->GetProjectionMatrix((f32)m_window->Width(), (f32)m_window->Height()));

	m_shaders["cube_light"]->Use();
	m_shaders["cube_light"]->SetUniform("view", m_camera->GetViewMatrix());
	m_shaders["cube_light"]->SetUniform("projection", m_camera->GetProjectionMatrix((f32)m_window->Width(), (f32)m_window->Height()));

	// Draw Models
	m_models[0]->Draw(m_shaders["core"]);
	m_models[1]->Draw(m_shaders["cube_light"]);
}