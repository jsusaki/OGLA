#include "SponzaScene.h"

SponzaScene::SponzaScene(std::shared_ptr<Window> window, std::shared_ptr<Input> input, std::shared_ptr<Camera> camera)
{
	m_window = window;
	m_input  = input;
	m_camera = std::move(camera);
}

void SponzaScene::OnCreate()
{
	// Create Shaders
	m_shaders = {
		{"core", std::make_shared<Shader>("./res/shaders/core.vert", "./res/shaders/core.frag")},
		{"cube_light", std::make_shared<Shader>("./res/shaders/cube_light.vert", "./res/shaders/cube_light.frag")},
	};

	// Create Cube Mesh
	Cube cube;
	// Create Light
	m_point_light = std::make_shared<PointLight>(
		vf3(1.2f, 1.0f, 2.0f),		// position
		vf3(0.2f, 0.2f, 0.2f),		// ambient
		vf3(0.5f, 0.5f, 0.5f),		// diffuse
		vf4(1.0f, 1.0f, 1.0f, 1.0f),// specular
		1.0f,						// constant
		0.09f,						// linear
		0.032f						// quadratic
	);	

	// Create Light Cube
	m_point_light = std::make_shared<PointLight>(
		vf3(1.2f, 1.0f, 2.0f),		// position
		vf3(0.2f, 0.2f, 0.2f),		// ambient
		vf3(0.5f, 0.5f, 0.5f),		// diffuse
		vf4(1.0f, 1.0f, 1.0f, 1.0f),// specular
		1.0f,						// constant
		0.09f,						// linear
		0.032f						// quadratic
	);
	std::shared_ptr<Model> light_cube = std::make_shared<Model>(cube);
	light_cube->SetPosition(m_point_light->m_position);
	light_cube->SetScale({ 0.2f, 0.2f, 0.2f });
	light_cube->SetName("light");
	m_models.push_back(light_cube);

	// Create Directional Light
	m_directional_light = std::make_shared<DirectionalLight>(
		vf3(-0.2f, -1.0f, -10.3f),	// direction
		vf3(0.2f, 0.2f, 0.2f),		// ambient
		vf3(0.5f, 0.5f, 0.5f),		// diffuse
		vf3(1.0f, 1.0f, 1.0f)		// specular
	);

	// Create Spot Light
	m_spot_light = std::make_shared<SpotLight>(
		m_camera->GetPosition(),		// position
		m_camera->GetFront(),			// direction
		vf3(0.0f, 0.0f, 0.0f),			// ambient
		vf3(1.0f, 1.0f, 1.0f),			// diffuse
		vf3(1.0f, 1.0f, 1.0f),			// specular
		1.0f,							// constant
		0.09f,							// linear
		0.032f,							// quadratic
		glm::cos(glm::radians(12.5f)),  // cutoff
		glm::cos(glm::radians(15.0f))   // outer cutoff
	);

	// Create Sponza Model
	//std::shared_ptr<Model> m_sponza = std::make_shared<Model>("./res/models/backpack/backpack.obj");
	std::shared_ptr<Model> m_sponza = std::make_shared<Model>("./res/models/sponza/sponza_obj/sponza.obj");
	// TODO: add texture mapping
	m_sponza->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_sponza->SetScale({ 0.25f, 0.25f, 0.25f });
	m_sponza->SetName("sponza");
	m_models.push_back(m_sponza);
}

void SponzaScene::OnActivate()
{

}

void SponzaScene::OnDeactivate()
{

}

void SponzaScene::OnProcessInput(f32 elapsed_time)
{

}

void SponzaScene::OnUpdate(f32 elapsed_time)
{

}

void SponzaScene::OnRender()
{
	// Update Uniforms
	m_point_light->Use(m_shaders["core"], 1);
	m_directional_light->Use(m_shaders["core"]);
	m_spot_light->Use(m_shaders["core"], m_camera->GetPosition(), m_camera->GetFront());
	
	m_shaders["core"]->Use();
	m_shaders["core"]->SetUniform("viewPos",    m_camera->GetPosition());
	m_shaders["core"]->SetUniform("view",       m_camera->GetViewMatrix());
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