#pragma once
#include <vector>
#include <memory>

#include "../Vertex/Vertex.h"
#include "../Vertex/VertexData.h"
#include "../Vertex/VertexBuffer.h"
#include "../Vertex/IndexBuffer.h"
#include "../Vertex/VertexArray.h"
#include "../Shader/Shader.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex>& vertices, VertexData& def);
	Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, VertexData& def);
	~Mesh();

public:
	void Draw();
	void Clear();

public:
	std::vector<Vertex> m_vertices;
	std::vector<u32> m_indices;
	VertexData m_def;
	std::shared_ptr<VertexBuffer> m_vbo;
	std::shared_ptr<IndexBuffer> m_ibo;
	std::shared_ptr<VertexArray> m_vao;
};