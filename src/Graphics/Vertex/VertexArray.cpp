#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vao);
}

VertexArray::VertexArray(const VertexBuffer& vbo, const VertexData& def)
{
	glGenVertexArrays(1, &m_vao);
	Bind(vbo, def);
}

VertexArray::VertexArray(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexData& def)
{
	glGenVertexArrays(1, &m_vao);
	Bind(vbo, ibo, def);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &m_vao);
}

void VertexArray::Bind(const VertexBuffer& vbo, const VertexData& def)
{
	vbo.Bind();
	glBindVertexArray(m_vao);
	for (u32 i = 0; i < def.Size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, def.GetCount(i), def.GetType(i), GL_FALSE, def.GetStride(), (const void*)def.GetOffset(i));
	}
	glBindVertexArray(0);
}

void VertexArray::Bind(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexData& def)
{
	glBindVertexArray(m_vao);
	vbo.Bind();
	ibo.Bind();
	for (u32 i = 0; i < def.Size(); i++)
	{	
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, def.GetCount(i), def.GetType(i), GL_FALSE, def.GetStride(), (const void*)def.GetOffset(i));
	}
	glBindVertexArray(0);
}