#include "Material.h"

Material::Material(f32 shininess, s32 diffuse_tex, s32 specular_tex, s32 emission_tex)
{
    m_shininess        = shininess;
	m_diffuse_texture  = diffuse_tex;
	m_specular_texture = specular_tex;
	m_emission_texture = emission_tex;
}

void Material::Use(const std::shared_ptr<Shader> shader)
{
    // TODO: Review implementation
    shader->Use();
    shader->SetUniform("material.shininess", m_shininess);

    if (m_diffuse_texture != -1)
    {
        glBindTexture(GL_TEXTURE_2D, m_diffuse_texture);
        shader->SetUniform("material.diffuse", m_diffuse_texture);
    }

    if (m_specular_texture != -1)
    {
        glBindTexture(GL_TEXTURE_2D, m_specular_texture);
        shader->SetUniform("material.specular", m_specular_texture);
    }

    if (m_emission_texture != -1)
    {
        glBindTexture(GL_TEXTURE_2D, m_emission_texture);
        shader->SetUniform("material.emission", m_emission_texture);
    }
};