#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vao);
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
}