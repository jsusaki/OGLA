#include "SandboxScene.h"

Sandbox::Sandbox(std::shared_ptr<Window> window, std::shared_ptr<Input> input, std::shared_ptr<Camera> camera)
{
	m_window = window;
	m_input = input;
	m_camera = std::move(camera);
}

void Sandbox::OnCreate()
{
	// Create Shaders
	m_shaders = {
		{"core", std::make_shared<Shader>("./res/shaders/core.vert", "./res/shaders/core.frag")},
		{"cube_light", std::make_shared<Shader>("./res/shaders/cube_light.vert", "./res/shaders/cube_light.frag")},
	};

	// Create Textures
	m_textures = {
		{"lisp",      std::make_shared<Texture>("./res/textures/lisp.jpg", "diffuse")},
		{"lisp_meta", std::make_shared<Texture>("./res/textures/meta-circular-evaluator.jpg", "diffuse")},
	};

	// Create Light Cube
	Cube cube;
	m_point_light = std::make_shared<PointLight>(
		vf3(1.2f, 1.0f, 2.0f),		// position
		vf3(0.2f, 0.2f, 0.2f),		// ambient
		vf3(0.5f, 0.5f, 0.5f),		// diffuse
		vf4(1.0f, 1.0f, 1.0f, 1.0f),// specular
		1.0f,						// constant
		0.09f,						// linear
		0.032f						// quadratic
	);
	std::shared_ptr<Model> light_cube = std::make_shared<Model>(cube.m_vertices, cube.m_indices);
	light_cube->SetPosition(m_point_light->m_position);
	light_cube->SetScale({ 0.2f, 0.2f, 0.2f });
	light_cube->SetName("light");
	m_models.push_back(light_cube);

	// Create Directional Light
	m_directional_light = std::make_shared<DirectionalLight>(
		vf3(-0.2f,-1.0f,-10.3f),	// direction
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

	// Create Material Cube
	std::vector<std::shared_ptr<Texture>> material_textures = { m_textures["lisp"], m_textures["lisp_meta"] };
	std::shared_ptr<Model> material_cube = std::make_shared<Model>(cube.m_vertices, cube.m_indices, material_textures); //  std::make_shared<Model>(cube);
	m_models.push_back(material_cube);

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
	m_directional_light->Use(m_shaders["core"]);
	m_point_light->Use(m_shaders["core"], NUM_POINT_LIGHTS); // syncronize with shader
	m_spot_light->Use(m_shaders["core"], m_camera->GetPosition(), m_camera->GetFront());

	m_shaders["core"]->Use();
	m_shaders["core"]->SetUniform("viewPos", m_camera->GetPosition());
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