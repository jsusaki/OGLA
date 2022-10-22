/*
	OGLA: OpenGL Abstraction
	
	OpenGL Renderer	
		Render Context
			Core
				Window Abstraction
				Event Abstraction
				Input Abstraction
					Keyboard Input
					Mouse Input
				Layer Abstraction

			Shader Abstraction
			Texture Abstraction
			Material Abstraction
			Light Abstraction
				Specular Light
				Spot Light

			Shadow Abstraction
			Camera Abstraction
				Orthographic Projection
				Perspective Projection

			Shape Abstraction
				Point
				Plane
				Cube

	TODO:
		Layer Abstraction
		Vertex Buffer Abstraction
		Vertex Array Abstraction
		Mesh Abstraction
		Shape Abstraction
			Cube

		Texture Abstraction
		Material Abstraction
		Light Abstraction
		Camera Abstraction
		Shader Abstraction

		Cube Rendering
		Cube Rendering Framework (Voxel Rendering)

	Useful Resouces:
	Voxel Engine Related
		Voxel Engine Tutorial: https://sites.google.com/site/letsmakeavoxelengine/
		Minecraft-Like Engines: https://0fps.net/2012/01/14/an-analysis-of-minecraft-like-engines/
		High Performance Voxel Engine: https://nickmcd.me/2021/04/04/high-performance-voxel-engine/
		JDH Minecraft Weekend: https://github.com/jdah/minecraft-weekend
	Engine Architecture
		OLC Pixel Game Engine: https://github.com/OneLoneCoder/olcPixelGameEngine
	OpenGL Fundamental and Abstraction
		Learn OpenGL: https://learnopengl.com/
		OpenGL Tutorial: http://www.opengl-tutorial.org/
		Open.GL: https://open.gl/
		OOGL: https://github.com/Overv/OOGL
*/

#include "Engine.h"

int main()
{
	Engine engine;
	if (engine.Init("OGLA: OpenGL Abstraction", 800, 600))
		engine.Start();
	return 0;
}