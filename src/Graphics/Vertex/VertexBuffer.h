#pragma once

#include <glad/glad.h>
#include <vector>

#include "../../Core/Common.h"
#include "Vertex.h"


enum BufferType
{
	STREAM_DRAW  = GL_STREAM_DRAW,
	STREAM_READ  = GL_STREAM_READ,
	STREAM_COPY  = GL_STREAM_COPY,
	STATIC_DRAW  = GL_STATIC_DRAW,
	STATIC_READ  = GL_STATIC_READ,
	STATIC_COPY  = GL_STATIC_COPY,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
	DYNAMIC_READ = GL_DYNAMIC_READ,
	DYNAMIC_COPY = GL_DYNAMIC_COPY
};

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const std::vector<Vertex>& data, BufferType type);
	~VertexBuffer();

public:
	void Bind() const;
	void Unbind() const;
	u32 GetVBO() const { return m_vbo; }

private:
	u32 m_vbo;
};

