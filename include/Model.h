#pragma once

#include <assimp/Importer.hpp>
#include <memory>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"


class Model
{
public:
	Model();
	Model(std::vector<Vertex>& vertices, std::vector<u32>& indices, VertexData& def);
	Model(Mesh& mesh);
	~Model();

public:
	void Draw(std::shared_ptr<Shader> shader);
	void Clear();

public:
	void Scale(const vf3& scale);
	void Rotate(const f32 angle, const vf3& axis);
	void Translate(const vf3& pos);

	void UpdateModelMatrix();
	mf4x4 GetModelMatrix() const;
	std::vector<Mesh> GetMeshes() const;
	vf3 GetPosition() const;
	vf3 GetRotation() const;
	vf3 GetScale() const;
	f32 GetAngle() const;

	void SetPosition(const vf3& pos);
	void SetRotation(const vf3& axis);
	void SetScale(const vf3& scale);
	void SetAngle(const f32 angle);

	void AddTexture(const std::shared_ptr<Texture>& texture);
	std::vector<std::shared_ptr<Texture>> GetTextures() const;
	
	void AddMaterial(const std::shared_ptr<Material>& material);
	std::vector<std::shared_ptr<Material>> GetMaterials() const;

private:
	std::string m_name;
	std::vector<Mesh> m_meshes;
	std::vector<std::shared_ptr<Texture>> m_textures;
	std::vector<std::shared_ptr<Material>> m_materials;
	mf4x4 m_model;

	// Transform POD?
	vf3 m_position;
	vf3 m_rotation;
	vf3 m_scale;
	f32 m_angle;
};