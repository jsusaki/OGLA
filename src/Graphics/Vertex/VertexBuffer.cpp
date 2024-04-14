#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{

}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vbo);
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& data, BufferType type)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data.front(), type);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}