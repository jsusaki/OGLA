#include "SceneStateMachine.h"

SceneStateMachine::SceneStateMachine()
{

}

void SceneStateMachine::Add(std::string name, std::shared_ptr<Scene> scene)
{
	auto inserted = m_scenes.insert(std::make_pair(name, scene));
	inserted.first->second->OnCreate();
}

void SceneStateMachine::TransitionTo(std::string name)
{
	auto it = m_scenes.find(name);
	if (it != m_scenes.end())
	{
		if (m_current_scene)
			m_current_scene->OnDeactivate();

		m_current_scene_name = name;
		m_current_scene = it->second;
		m_current_scene->OnActivate();
	}
}

void SceneStateMachine::Remove(std::string name)
{
	auto it = m_scenes.find(name);
	if (it != m_scenes.end())
	{
		if (m_current_scene == it->second)
			m_current_scene = nullptr;

		m_scenes.erase(it);
	}
}

void SceneStateMachine::Init()
{
	if (m_current_scene != nullptr)
		m_current_scene->OnCreate();
}

void SceneStateMachine::ProcessInput(f32 fElapsedTime)
{
	if (m_current_scene != nullptr)
		m_current_scene->OnProcessInput(fElapsedTime);
}

void SceneStateMachine::Update(f32 fElapsedTime)
{
	if (m_current_scene != nullptr)
		m_current_scene->OnUpdate(fElapsedTime);
}

void SceneStateMachine::Render()
{
	if (m_current_scene != nullptr)
		m_current_scene->OnRender();
}
