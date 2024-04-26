#include "Mesh.h"

Mesh::Mesh()
{
	m_vbo = nullptr;
	m_ibo =	nullptr;
	m_vao =	nullptr;
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices)
{
	m_vertices = vertices;
	m_indices  = indices;

	// Create Vertex Buffer Definition
	m_def.Add<vf3>(); // position
	m_def.Add<vf3>(); // normal
	m_def.Add<vf2>(); // texcoords
	m_def.Add<vf4>(); // color
	m_def.Add<vf3>(); // tangent
	m_def.Add<vf3>(); // bitangent

	m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
	m_ibo = std::make_shared<IndexBuffer>(m_indices, STATIC_DRAW);
	m_vao = std::make_shared<VertexArray>(*m_vbo, *m_ibo, m_def);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<std::shared_ptr<Texture>>& textures)
{
	m_vertices  = vertices;
	m_indices   = indices;
	m_textures  = textures;

	// Create Vertex Buffer Definition
	m_def.Add<vf3>(); // position
	m_def.Add<vf3>(); // normal
	m_def.Add<vf2>(); // texcoords
	m_def.Add<vf4>(); // color
	m_def.Add<vf3>(); // tangent
	m_def.Add<vf3>(); // bitangent

	m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
	m_ibo = std::make_shared<IndexBuffer>(m_indices, STATIC_DRAW);
	m_vao = std::make_shared<VertexArray>(*m_vbo, *m_ibo, m_def);
}

/*
TODO: Implement Material class
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::shared_ptr<Material> material)
{
	m_vertices  = vertices;
	m_indices   = indices;
	m_material  = material;

	// Create Vertex Buffer Definition
	m_def.Add<vf3>(); // position
	m_def.Add<vf3>(); // normal
	m_def.Add<vf2>(); // texcoords
	m_def.Add<vf4>(); // color
	m_def.Add<vf3>(); // tangent
	m_def.Add<vf3>(); // bitangent

	m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
	m_ibo = std::make_shared<IndexBuffer>(m_indices, STATIC_DRAW);
	m_vao = std::make_shared<VertexArray>(*m_vbo, *m_ibo, m_def);
}
*/

void Mesh::Draw(const std::shared_ptr<Shader> shader)
{
	//if (m_material) m_material->Use(shader);
	// TODO: Abstract into material class
	for (s32 i = 0; i < m_textures.size(); i++)
	{
		// Set texture unit
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = m_textures[i]->GetType();

		// Set material texture uniforms
		// TODO: set shininess programmatically
		shader->Use();
		shader->SetUniform("material.shininess", 64.0f);
		shader->SetUniform("material." + name, i);

		// Bind texture
		m_textures[i]->Bind();
	}

	glBindVertexArray(m_vao->GetVAO());
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
