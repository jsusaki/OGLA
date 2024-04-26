#include "Light.h"

DirectionalLight::DirectionalLight(vf3 direction, vf3 ambient, vf3 diffuse, vf3 specular) 
{
	m_direction = direction;
	m_ambient   = ambient;
	m_diffuse   = diffuse;
	m_specular  = specular;
}

void DirectionalLight::Use(std::shared_ptr<Shader> shader)
{
	shader->Use();
	shader->SetUniform("dirLight.direction", m_direction);
	shader->SetUniform("dirLight.ambient",   m_ambient);
	shader->SetUniform("dirLight.diffuse",   m_diffuse);
	shader->SetUniform("dirLight.specular",  m_specular);
}

PointLight::PointLight(vf3 position, vf3 ambient, vf3 diffuse, vf3 specular, f32 constant, f32 linear, f32 quadratic)
{
	m_position  = position;
	m_ambient   = ambient;
	m_diffuse   = diffuse;
	m_specular  = specular;
	m_constant  = constant;
	m_linear    = linear;
	m_quadratic = quadratic;
}

void PointLight::Use(std::shared_ptr<Shader> shader, s32 n_point_lights)
{
	for (s32 i = 0; i < n_point_lights; i++)
	{
		shader->Use();
		std::string uniform_loc = std::format("pointLights[{}]", i);
		shader->SetUniform(uniform_loc + ".position",  m_position);
		shader->SetUniform(uniform_loc + ".ambient",   m_ambient);
		shader->SetUniform(uniform_loc + ".diffuse",   m_diffuse);
		shader->SetUniform(uniform_loc + ".specular",  m_specular);
		shader->SetUniform(uniform_loc + ".constant",  m_constant);
		shader->SetUniform(uniform_loc + ".linear",    m_linear);
		shader->SetUniform(uniform_loc + ".quadratic", m_quadratic);
	}
}

SpotLight::SpotLight(vf3 position, vf3 direction, vf3 ambient, vf3 diffuse, vf3 specular, f32 constant, f32 linear, f32 quadratic, f32 cutoff, f32 outer_cutoff)
{
	m_position     = position;
	m_direction    = direction;
	m_ambient      = ambient;
	m_diffuse      = diffuse;
	m_specular     = specular;
	m_constant     = constant;
	m_linear       = linear;
	m_quadratic    = quadratic;
	m_cutoff       = cutoff;
	m_outer_cutoff = outer_cutoff;
}

void SpotLight::Use(std::shared_ptr<Shader> shader, vf3 pos, vf3 dir)
{
	shader->Use();
	shader->SetUniform("spotLight.position",  pos);
	shader->SetUniform("spotLight.direction", dir);
	shader->SetUniform("spotLight.ambient",   m_ambient);
	shader->SetUniform("spotLight.diffuse",   m_diffuse);
	shader->SetUniform("spotLight.specular",  m_specular);
	shader->SetUniform("spotLight.constant",  m_constant);
	shader->SetUniform("spotLight.linear",    m_linear);
	shader->SetUniform("spotLight.quadratic", m_quadratic);
	shader->SetUniform("spotLight.cutOff",    m_cutoff);
	shader->SetUniform("spotLight.outerCutOff", m_outer_cutoff);
}