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
#include <unordered_map>

#include <glad/glad.h>

#include "Type.h"


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

public:
	std::string LoadFromFile(const std::string& filepath);
	u32 Compile(ShaderType type, std::string& source);
	void Attach(u32& shader);
	void Link();
	void Detach(u32& shader);
	void Delete(u32& shader);

public:
	u32 GetAttribute(const std::string& name) const;
	u32 GetUniform(const std::string& name)  const;
	void SetUniform(const std::string& name, const s32& val);
	void SetUniform(const std::string& name, f32* val, s32 count);
	void SetUniform(const std::string& name, s32* val, s32 count);
	void SetUniform(const std::string& name, const f64& val);
	void SetUniform(const std::string& name, const f32& val);
	void SetUniform(const std::string& name, const vf2& vector);
	void SetUniform(const std::string& name, const vf3& vector);
	void SetUniform(const std::string& name, const vf4& vector);
	void SetUniform(const std::string& name, const mf4x4& matrix);

private:
	u32 m_ProgramID;
	mutable std::unordered_map<std::string, u32> m_UniformLocations;
};
