/*
	Phong Lighting
		Ambient Lighting: ambient lighting constant that always gives the object some color
		Diffuse Lighting: simulates the directional impact a light object has on an object
		Specular Lighting: simulates the bright spot of a light that appears on shiny objects
*/
#pragma once

#include <memory>

#include "../../Core/Common.h"
#include "../Shader/Shader.h"

struct Light
{
	vf3 m_ambient;
	vf3 m_diffuse;
	vf3 m_specular;
};

// REDESIGN: Use() method to take be able to update during runtime
class DirectionalLight : public Light
{
public:
	DirectionalLight(vf3 direction, vf3 ambient, vf3 diffuse, vf3 specular);
	void Use(std::shared_ptr<Shader> shader);
public:
	vf3 m_direction;
};

class PointLight : public Light
{
public:
	PointLight(vf3 position, vf3 ambient, vf3 diffuse, vf3 specular, f32 constant, f32 linear, f32 quadratic);
	void Use(std::shared_ptr<Shader> shader, s32 n_point_lights);
public:
	vf3 m_position;
	f32 m_constant;
	f32 m_linear;
	f32 m_quadratic;
};

static const s32 NUM_POINT_LIGHTS = 1;

class SpotLight : public Light
{
public:
	SpotLight(vf3 position, vf3 direction, vf3 ambient, vf3 diffuse, vf3 specular, f32 constant, f32 linear, f32 quadratic, f32 cut_off, f32 outer_cut_off);
	void Use(std::shared_ptr<Shader> shader, vf3 pos, vf3 dir);
public:
	vf3 m_position;
	vf3 m_direction;
	f32 m_cutoff;
	f32 m_outer_cutoff;
	f32 m_constant;
	f32 m_linear;
	f32 m_quadratic;
};