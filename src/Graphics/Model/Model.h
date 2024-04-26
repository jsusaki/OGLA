#pragma once

#include <vector>
#include <memory>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Mesh/Mesh.h"
#include "../Texture/Texture.h"
#include "../Material/Material.h"


class Model
{
public:
	Model();
	Model(std::vector<Vertex>& vertices, std::vector<u32>& indices);
	//Model(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::shared_ptr<Material> material);
	Model(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<std::shared_ptr<Texture>> texture);
	Model(Mesh& mesh);
	Model(const std::string& path);

public:
	void Draw(std::shared_ptr<Shader> shader);

public:
	void Scale(const vf3& scale);
	void Rotate(const f32 angle, const vf3& axis);
	void Translate(const vf3& pos);

	void UpdateModelMatrix();
	mf4x4 GetModelMatrix() const;
	std::vector<Mesh> GetMeshes() const;
	vf3 GetPosition() const;
	void SetPosition(const vf3& pos);
	vf3 GetRotation() const;
	void SetRotation(const vf3& axis);
	vf3 GetScale() const;
	void SetScale(const vf3& scale);
	f32 GetAngle() const;
	void SetAngle(const f32 angle);
	std::string GetName();
	void SetName(std::string name);

	void AddTexture(const std::shared_ptr<Texture>& texture);
	std::vector<std::shared_ptr<Texture>> GetTextures() const;

public: // Assimp model loading
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Vertex> ProcessVertices(aiMesh* mesh, const aiScene* scene);
	std::vector<u32> ProcessIndices(aiMesh* mesh);
	std::vector<std::shared_ptr<Texture>> ProcessMaterials(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

private:
	std::string m_name;
	std::string m_directory;
	std::vector<Mesh> m_meshes;
	std::vector<std::shared_ptr<Texture>> m_textures;
	mf4x4 m_model;

	vf3 m_position;
	vf3 m_rotation;
	vf3 m_scale;
	f32 m_angle;
};