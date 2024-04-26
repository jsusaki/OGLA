/*
	OGLA: OpenGL Abstraction
	
	OpenGL Renderer	
		Core
			Window
			Event
			Input
				Keyboard Input
				Mouse Input
		Graphics
			Vertex
			Vertex Buffer
			Index Buffer
			Vertex Data 
			Shader
			Texture
			Mesh
				Triangle
				Quad (Plane)
				Cube
			Model
			Camera
				Orthographic Camera
				Perspective Camera
				Orbit Camera
			Material
				PBR material
			Light
				Phong Lighting
				Blinn-Phong Lighting
		Scene
		Scene State Machine
		3D Asset Import: Assimp

	TODO:
		Refactor std::shared_ptr<> to consider object lifetime for performance optimization

		Add Namespace OGLA
		GUI: ImGui

		Logging System
			Shader
			Texture
			Model
		Layer
		Shadow

		Voxel Rendering Framework

	Useful Resources: 
		Voxel Engine
			Voxel Engine Tutorial: https://sites.google.com/site/letsmakeavoxelengine/
			Minecraft-Like Engines: https://0fps.net/2012/01/14/an-analysis-of-minecraft-like-engines/
			High Performance Voxel Engine: https://nickmcd.me/2021/04/04/high-performance-voxel-engine/
			JDH Minecraft Weekend: https://github.com/jdah/minecraft-weekend
		Engine Architecture
			OLC Pixel Game Engine: https://github.com/OneLoneCoder/olcPixelGameEngine
			Enjon: https://github.com/MrFrenik/Enjon
		OpenGL Fundamental and Abstraction
			Learn OpenGL: https://learnopengl.com/
			OpenGL Tutorial: http://www.opengl-tutorial.org/
			Open.GL: https://open.gl/
			OOGL: https://github.com/Overv/OOGL
			songho: http://www.songho.ca/opengl/index.html
			grid: https://asliceofrendering.com/scene%20helper/2020/01/05/InfiniteGrid/
*/
#include "Core/Engine.h"

//TODO: Move to Examples/
#include "Scenes/SandboxScene.h"
#include "Scenes/CubeScene.h"
#include "Scenes/SponzaScene.h"

class Application : public Engine
{
public:
	Application() 
	{
	
	}

public:
	bool OnCreate() override
	{
		// Create Camera
		m_camera = std::make_shared<Camera>(vf3{ 0.0f, 0.0f, 3.0f });
		// Z-Fighting: set near plane to something like:L 1.0f, 2.0f, 5.0f, or 10.0f

		// Create Scene
		// TODO: pass engine instead of window, input, camera?
		// REDESIGN: if we make window and input static, we can access globally
		// TODO: Scene is being created when we call Add(), it should create when we instantiate
		std::shared_ptr<Scene> sandbox = std::make_shared<Sandbox>(m_window, m_input, m_camera);
		m_scene_state->Add("sandbox", sandbox);

		std::shared_ptr<Scene> cube_scene = std::make_shared<CubeScene>(m_window, m_input, m_camera);
		m_scene_state->Add("cube_scene", cube_scene);

		std::shared_ptr<Scene> sponza_scene = std::make_shared<SponzaScene>(m_window, m_input, m_camera);
		m_scene_state->Add("sponza_scene", sponza_scene);

		// Set Active Scene
		m_scene_state->TransitionTo("sandbox");

		return true;
	}

	bool OnUpdate(f32 elapsed_time) override
	{
		// Application Control
		if (m_input->GetKey(Key::ESC).pressed) m_window->Close();
		if (m_input->GetKey(Key::TAB).pressed) m_window->ToggleMouseFocus();
		if (m_input->GetKey(Key::F11).pressed) m_window->ToggleFullScreen();
		// Rendering Mode Control
		if (m_input->GetKey(Key::K1).pressed)  m_window->SetRenderMode(RenderMode::NORMAL);
		if (m_input->GetKey(Key::K2).pressed)  m_window->SetRenderMode(RenderMode::WIREFRAME);

		// Camera Mode Control
		if (m_input->GetKey(Key::F1).pressed)  m_camera->SetMode(CameraMode::PERSPECTIVE);
		if (m_input->GetKey(Key::F2).pressed)  m_camera->SetMode(CameraMode::ORTHOGRAPHIC);
		if (m_input->GetKey(Key::F3).pressed)  m_camera->SetMode(CameraMode::ORBIT);
		// Camera Key Control
		if (m_camera->GetMode() == CameraMode::PERSPECTIVE)
		{
			if (m_input->GetKey(Key::W).held) m_camera->KeyControl(Direction::FORWARD, elapsed_time);
			if (m_input->GetKey(Key::S).held) m_camera->KeyControl(Direction::BACKWARD, elapsed_time);
			if (m_input->GetKey(Key::A).held) m_camera->KeyControl(Direction::LEFT, elapsed_time);
			if (m_input->GetKey(Key::D).held) m_camera->KeyControl(Direction::RIGHT, elapsed_time);
			if (m_input->GetKey(Key::Q).held) m_camera->KeyControl(Direction::DOWN, elapsed_time);
			if (m_input->GetKey(Key::E).held) m_camera->KeyControl(Direction::UP, elapsed_time);

			m_camera->MouseControl(m_input->GetMousePos());
			m_camera->MousePanControl(m_input->GetMousePos());
		}
		// TODO: Make Orbit Camera Control More Intuitive
		else if (m_camera->GetMode() == CameraMode::ORBIT)
		{
			if (m_input->GetMouse(0).held)
				m_camera->MouseOrbitControl(m_input->GetMousePos()); // Jumping position when go back to perspective; store position?
			if (m_input->GetMouse(1).held)
				m_camera->MousePanControl(m_input->GetMousePos());
		}
		else if (m_camera->GetMode() == CameraMode::ORTHOGRAPHIC)
		{
			if (m_input->GetMouse(0).held)
				m_camera->MouseOrbitControl(m_input->GetMousePos());
			if (m_input->GetMouse(1).held)
				m_camera->MousePanControl(m_input->GetMousePos());
		}
		// Camera Mouse Control
		m_camera->MouseScrollControl(m_input->GetMouseWheel());
		// DEBUG
		//std::println("Mouse Pos: {}, {}", m_input->GetMousePos().x, m_input->GetMousePos().y);
		//std::println("Mouse Delta: {}, {}", m_input->GetMouseDelta().x, m_input->GetMouseDelta().y);
		//std::println("Camera Pos: {}, {}, {}", m_camera->GetPosition().x, m_camera->GetPosition().y, m_camera->GetPosition().z);

		// Scene Control
		if (m_input->GetKey(Key::NP1).pressed)
			m_scene_state->TransitionTo("sandbox");
		if (m_input->GetKey(Key::NP2).pressed)
			m_scene_state->TransitionTo("cube_scene");
		if (m_input->GetKey(Key::NP3).pressed)
			m_scene_state->TransitionTo("sponza_scene");

		return true;
	}

private:
	std::shared_ptr<Camera> m_camera;
};


int main()
{
	Application app;
	if (app.Init("OGLA: OpenGL Abstraction", 1280, 720))
		app.Start();
	return 0;
}