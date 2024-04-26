#pragma once
#include <vector>
#include <memory>

#include "../Vertex/Vertex.h"
#include "../Vertex/VertexData.h"
#include "../Vertex/VertexBuffer.h"
#include "../Vertex/IndexBuffer.h"
#include "../Vertex/VertexArray.h"
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"
#include "../Material/Material.h"


class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices);
	//Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::shared_ptr<Material> material);
	Mesh(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<std::shared_ptr<Texture>>& textures);

public:
	void Draw(const std::shared_ptr<Shader> shader);

public:
	VertexData m_def; // Defines the layout of the vertex data
	std::vector<Vertex> m_vertices;
	std::vector<u32> m_indices;
	std::vector<std::shared_ptr<Texture>> m_textures;
	//std::shared_ptr<Material> m_material;

	std::shared_ptr<VertexBuffer> m_vbo;
	std::shared_ptr<IndexBuffer>  m_ibo;
	std::shared_ptr<VertexArray>  m_vao;
};