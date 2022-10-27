#pragma once
#include <glad/glad.h>

#include "Common.h"
#include "VertexData.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

public:
	void Bind(const VertexBuffer& vbo, const VertexData& def);
	u32 GetVAO() { return m_vao; }

private:
	u32 m_vao;
};