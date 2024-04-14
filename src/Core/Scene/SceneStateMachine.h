#pragma once

#include <memory>
#include <map>
#include <string>

#include "../Common.h"
#include "Scene.h"


class SceneStateMachine
{
public:
	SceneStateMachine();

public:
	void Add(std::string name, std::shared_ptr<Scene> scene);
	void TransitionTo(std::string name);
	void Remove(std::string name);

public:
	void Init();
	void ProcessInput(f32 fElapsedTime);
	void Update(f32 fElapsedTime);
	void Render();

private:
	std::shared_ptr<Scene> m_current_scene;
	std::string m_current_scene_name;
	std::map<std::string, std::shared_ptr<Scene>> m_scenes;
};