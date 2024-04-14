#pragma once
#include <memory>

#include "../../Core/Common.h"
#include "../Shader/Shader.h"

class Material
{
public:
	Material(f32 shininess, s32 diffuse_texture, s32 specular_texture, s32 emission_texture);

	void Use(std::shared_ptr<Shader> shader);
public:
	f32 m_shininess;
	s32 m_diffuse_texture;
	s32 m_specular_texture;
	s32 m_emission_texture;
};