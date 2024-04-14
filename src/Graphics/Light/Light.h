/*
	Phong Lighting
		Ambient Lighting: ambient lighting constant that always gives the object some color
		Diffuse Lighting: simulates the directional impact a light object has on an object
		Specular Lighting: simulates the bright spot of a light that appears on shiny objects

	What is the intelligible light structure?
	
	Material
		ambient
		diffuse
		specular
	
	Light
		color
		intensity

	Directional Light
		position
		direction

	Point Light
	Spot Light
*/
#pragma once

#include <memory>

#include "../../Core/Common.h"
#include "../Shader/Shader.h"

class Light
{
public:
	Light(vf3 position, vf3 ambient, vf3 diffuse, vf3 specular);

	void Use(std::shared_ptr<Shader> shader);

public:
	vf3 m_position;
	vf3 m_ambient;
	vf3 m_diffuse;
	vf3 m_specular;
};