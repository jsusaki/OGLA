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
			Vertex Abstraction
			Vertex Buffer Abstraction
			Index Buffer Abstraction
			Vertex Array Abstraction
			Vertex Data Abstraction
			Shader Abstraction
			Texture Abstraction
			Mesh Abstraction
				Triangle
				Quad (Plane)
				Cube
			Model Abstration
			Camera Abstraction
				Orthographic Projection
				Perspective Projection
			Material Abstraction
				PBR material
			Light Abstraction
				Phong Lighting
				Binn-Phong Lighting
    		Scene Abstraction
    		State Machine Abstraction

	TODO:
		Asset Import
		Layer Abstraction
		Shadow Abstraction

		Voxel Rendering
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
*/
#include "Engine.h"

int main()
{
	Engine engine;
	if (engine.Init("OGLA: OpenGL Abstraction", 800, 600))
		engine.Start();
	return 0;
}