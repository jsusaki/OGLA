#pragma once

#include <glad/glad.h>
#include <vector>

#include "Type.h"
#include "Vertex.h"
#include "VertexBuffer.h"


class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(const std::vector<u32>& data, BufferType type);
	~IndexBuffer();

public:
	void Bind() const;
	void Unbind() const;
	u32 GetVBO() const { return m_ibo; }

private:
	u32 m_ibo;
};

