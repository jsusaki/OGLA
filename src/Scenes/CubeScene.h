#pragma once
#include "../Core/Scene/Scene.h"
#include "../Core/Common.h"
#include "../Core/Window/Window.h"
#include "../Core/Input/Input.h"

#include "../Graphics/Shader/Shader.h"
#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Model/Model.h"
#include "../Graphics/Shape/Shape.h"
#include "../Graphics/Light/Light.h"
#include "../Graphics/Material/Material.h"
#include "../Graphics/Camera/Camera.h"

class CubeScene : public Scene
{
public:
	CubeScene(std::shared_ptr<Window> window, std::shared_ptr<Input> input, std::shared_ptr<Camera> camera);
public:
	void OnCreate() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnProcessInput(f32 elapsed_time) override;
	void OnUpdate(f32 elapsed_time) override;
	void OnRender() override;
private:
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Input> m_input;
	std::shared_ptr<Camera> m_camera;

	// Scene objects
	f32 acc_timer;
	std::map<std::string, std::shared_ptr<Shader>> m_shaders;
	std::map<std::string, std::shared_ptr<Texture>> m_textures;
	std::vector<std::shared_ptr<Model>> m_models;
	std::shared_ptr<Light> m_light;
	std::shared_ptr<Material> m_material;
};