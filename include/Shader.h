/*
	Shader Type
		Vertex Shader  : transform 3D coordinates into different 3D coordinates
		Fragment shader: calculate the final color of a pixel
		Geometry Shader: generate other shapes by emitting new vertices to form new primitive

	Shader Program
		Load   : load shader source from file
		Compile: compile shader source
		Attach : attach shader to program
		Link   : link shader to program
		Use    : use shader program
*/

#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include <glad/glad.h>

#include "Common.h"

enum ShaderType
{
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER
};

class Shader
{
public:
	Shader();
	Shader(const std::string& vertex_path, const std::string& fragment_path);
	~Shader();

public:
	void Use();
	void Unuse();
	u32 GetID();
	u32 GetAttribute(const std::string& name);
	u32 GetUniform(const std::string& name);

public:
	std::string LoadFromFile(const std::string& filepath);
	u32 Compile(ShaderType type, std::string& source);
	void Attach(u32& shader);
	void Link();
	void Detach(u32& shader);
	void Delete(u32& shader);

private:
	u32 m_ProgramID;
};
