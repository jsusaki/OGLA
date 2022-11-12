#pragma once

#include <map>
#include <memory>

#include "Window.h"
#include "Input.h"
#include "Type.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Shape.h"
#include "Light.h"
#include "Material.h"


class Scene
{
public:
	virtual ~Scene() {};
	virtual void Init() = 0;
	virtual void ProcessInput(f32 fElapsedTime) = 0;
	virtual void Update(f32 fElapsedTime) = 0;
	virtual void Render() = 0;
};


class Sandbox : public Scene
{
public:
	Sandbox(std::shared_ptr<Window> window, std::shared_ptr<Input> input);
public:
	void Init() override;
	void ProcessInput(f32 fElapsedTime) override;
	void Update(f32 fElapsedTime) override;
	void Render() override;
private:
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Input> m_input;
	// Scene objects
	f32 acc_timer;
	std::map<std::string, std::shared_ptr<Shader>> m_shaders;
	std::map<std::string, std::shared_ptr<Texture>> m_textures;
	std::vector<std::shared_ptr<Model>> m_models;
	std::unique_ptr<Camera> m_camera;
	std::shared_ptr<Light> m_light;
	std::shared_ptr<Material> m_material;
};