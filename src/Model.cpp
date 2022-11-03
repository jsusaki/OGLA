#include "Model.h"

Model::Model()
{
	m_model = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale = vf3(1.0f, 1.0f, 1.0f);
	m_angle = 0.0f;
}

Model::Model(std::vector<Vertex>& vertices, std::vector<u32>& indices, VertexData& def)
{
	m_model = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale = vf3(1.0f, 1.0f, 1.0f);
	m_angle = 0.0f;

	m_meshes.push_back({ vertices, indices, def });
}

Model::~Model()
{

}

void Model::Draw(std::shared_ptr<Shader> shader)
{
	shader->Use();
	UpdateModelMatrix();
	shader->SetUniform("model", m_model);

	for (u32 i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		m_textures[i]->Bind();
	}

	for (auto& mesh : m_meshes)
		mesh.Draw();
}

void Model::Clear()
{

}


void Model::Scale(const vf3& scale)
{
	m_scale = scale;
}

void Model::Rotate(const f32 angle, const vf3& axis)
{
	m_rotation = axis;
	m_angle = angle;
}

void Model::Translate(const vf3& pos)
{
	m_position = pos;
}

void Model::UpdateModelMatrix()
{
	m_model = mf4x4(1.0f);
	m_model = glm::rotate(m_model, glm::radians(m_angle), m_rotation);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::scale(m_model, m_scale);
}

mf4x4 Model::GetModelMatrix() const
{
	return m_model;
}

std::vector<Mesh> Model::GetMeshes() const
{
	return m_meshes;
}

vf3 Model::GetPosition() const
{
	return m_position;
}

vf3 Model::GetRotation() const
{
	return m_rotation;
}

vf3 Model::GetScale() const
{
	return m_scale;
}

f32 Model::GetAngle() const
{
	return m_angle;
}