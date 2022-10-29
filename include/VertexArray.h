#pragma once

#include <glad/glad.h>

#include "Type.h"
#include "VertexData.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	VertexArray(const VertexBuffer& vbo, const VertexData& def);
	VertexArray(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexData& def);
	~VertexArray();

public:
	void Bind(const VertexBuffer& vbo, const VertexData& def);
	void Bind(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexData& def);
	u32 GetVAO() { return m_vao; }

private:
	u32 m_vao;
};