#pragma once

#include "../../Core/Common.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"


class Material
{
public:
	Material(f32 shininess, s32 diffuse_tex, s32 specular_tex, s32 emission_tex);

public:
	void Use(const std::shared_ptr<Shader> shader);

public:
	f32 m_shininess;
	// refactor to Texture class
	s32 m_diffuse_texture;	// texture_id
	s32 m_specular_texture; // texture_id
	s32 m_emission_texture; // texture_id
};