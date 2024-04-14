#include "Material.h"

Material::Material(f32 shininess, s32 diffuse_texture, s32 specular_texture, s32 emission_texture)
{
	m_shininess = shininess;
	m_diffuse_texture = diffuse_texture;
	m_specular_texture = specular_texture;
	m_emission_texture = emission_texture;
}

void Material::Use(std::shared_ptr<Shader> shader)
{
	shader->Use();
	shader->SetUniform("material.diffuse", m_diffuse_texture);
	if (m_specular_texture != -1)
		shader->SetUniform("material.specular", m_specular_texture);
	if (m_emission_texture != -1)
		shader->SetUniform("material.emission", m_emission_texture);
	shader->SetUniform("material.shininess", m_shininess);
}
