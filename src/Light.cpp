#include "Light.h"

Light::Light(vf3 position, vf3 ambient, vf3 diffuse, vf3 specular)
{
	m_position = position;
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
}

void Light::Use(std::shared_ptr<Shader> shader)
{
	shader->Use();
	shader->SetUniform("light.position", m_position);
	shader->SetUniform("light.ambient", m_ambient);
	shader->SetUniform("light.diffuse", m_diffuse);
	shader->SetUniform("light.specular",  m_specular);
}
