#include "Scene.h"

Sandbox::Sandbox(std::shared_ptr<Window> window, std::shared_ptr<Input> input, std::shared_ptr<Camera> camera)
{
	m_window = window;
	m_input = input;
	m_camera = std::move(camera);
}

void Sandbox::OnCreate()
{
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

void Sandbox::OnActivate()
{

}

void Sandbox::OnDeactivate()
{
}

void Sandbox::OnProcessInput(f32 elapsed_time)
{

}

void Sandbox::OnUpdate(f32 elapsed_time)
{
	acc_timer += elapsed_time;
}

void Sandbox::OnRender()
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



// Cube Scene
CubeScene::CubeScene(std::shared_ptr<Window> window, std::shared_ptr<Input> input, std::shared_ptr<Camera> camera)
{
	m_window = window;
	m_input = input;
	m_camera = std::move(camera);
}

void CubeScene::OnCreate()
{
	// Create Cube
	Cube cube;

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
		{ 6.4f,-10.4f,-13.5f},
		{-6.7f, 7.0f,-17.5f },
		{ 6.3f,-6.0f,-12.5f },
		{ 6.5f, 6.0f,-12.5f },
		{ 6.5f, 5.2f,-11.5f },
		{-6.3f, 6.0f,-11.5f }
	};

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
	std::shared_ptr<Model> light_cube = std::make_shared<Model>(cube);
	light_cube->SetPosition(m_light->m_position);
	light_cube->SetScale({ 0.2f, 0.2f, 0.2f });
	light_cube->SetName("light");
	m_models.push_back(light_cube);

	// Create Models
	for (u32 i = 0; i < CubePositions.size(); i++)
	{
		std::shared_ptr<Model> material_cube = std::make_shared<Model>(cube);
		material_cube->AddTexture(m_textures["lisp"]);
		material_cube->AddTexture(m_textures["lisp_meta"]);
		material_cube->AddMaterial(m_material);
		material_cube->Translate(CubePositions[i]);
		material_cube->SetName("cube_" + i);
		m_models.push_back(material_cube);
	}
}

void CubeScene::OnActivate()
{

}

void CubeScene::OnDeactivate()
{

}

void CubeScene::OnProcessInput(f32 fElapsedTime)
{

}

void CubeScene::OnUpdate(f32 fElapsedTime)
{

}

void CubeScene::OnRender()
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
	for (auto& m : m_models)
	{
		if (m->GetName() == "light")
			m->Draw(m_shaders["cube_light"]);
		else
			m->Draw(m_shaders["core"]);
	}
}