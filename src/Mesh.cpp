#include "Mesh.h"

Mesh::Mesh()
{
	m_vbo = nullptr;
	m_ibo =	nullptr;
	m_vao =	nullptr;
}

Mesh::Mesh(std::vector<Vertex>& vertices, VertexData& def)
{
	m_vertices = vertices;
	m_def = def;

	m_ibo = nullptr;
	m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
	m_vao = std::make_shared<VertexArray>(*m_vbo, def);
}


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, VertexData& def)
{
	m_vertices = vertices;
	m_indices = indices;
	m_def = def;

	m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
	m_ibo = std::make_shared<IndexBuffer>(m_indices, STATIC_DRAW);
	m_vao = std::make_shared<VertexArray>(*m_vbo, *m_ibo, m_def);
}

Mesh::~Mesh()
{

}

void Mesh::Draw()
{
	glBindVertexArray(m_vao->GetVAO());
	if (m_ibo != nullptr)
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

void Mesh::Clear()
{

}
