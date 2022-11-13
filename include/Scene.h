#pragma once

#include <map>

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
	virtual void OnCreate() {};
	virtual void OnActivate() {};
	virtual void OnDeactivate() {};
	virtual void OnProcessInput(f32 fElapsedTime) {};
	virtual void OnUpdate(f32 fElapsedTime) {};
	virtual void OnRender() {};
};


class Sandbox : public Scene
{
public:
	Sandbox(std::shared_ptr<Window> window, std::shared_ptr<Input> input, std::shared_ptr<Camera> camera);
public:
	void OnCreate() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnProcessInput(f32 fElapsedTime) override;
	void OnUpdate(f32 fElapsedTime) override;
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

class CubeScene : public Scene
{
public:
	CubeScene(std::shared_ptr<Window> window, std::shared_ptr<Input> input, std::shared_ptr<Camera> camera);
public:
	void OnCreate() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnProcessInput(f32 fElapsedTime) override;
	void OnUpdate(f32 fElapsedTime) override;
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