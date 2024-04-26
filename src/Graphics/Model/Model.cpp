#include "Model.h"

Model::Model()
{
	m_model    = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale    = vf3(1.0f, 1.0f, 1.0f);
	m_angle    = 0.0f;
}

Model::Model(std::vector<Vertex>& vertices, std::vector<u32>& indices)
{
	m_model    = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale    = vf3(1.0f, 1.0f, 1.0f);
	m_angle    = 0.0f;

	m_meshes.push_back({ vertices, indices });
}

/*
Model::Model(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::shared_ptr<Material> material)
{
	m_model    = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale    = vf3(1.0f, 1.0f, 1.0f);
	m_angle    = 0.0f;
	
	m_meshes.push_back({ vertices, indices, material });
}
*/

Model::Model(std::vector<Vertex>& vertices, std::vector<u32>& indices, std::vector<std::shared_ptr<Texture>> texture)
{
	m_model    = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale    = vf3(1.0f, 1.0f, 1.0f);
	m_angle    = 0.0f;

	m_meshes.push_back({ vertices, indices, texture });
}

Model::Model(Mesh& mesh)
{
	m_model    = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale    = vf3(1.0f, 1.0f, 1.0f);
	m_angle    = 0.0f;

	m_meshes.push_back(mesh);
}

Model::Model(const std::string& path)
{
	m_model    = mf4x4(1.0f);
	m_position = vf3(0.0f, 0.0f, 0.0f);
	m_rotation = vf3(0.0f, 0.0f, 0.0f);
	m_scale    = vf3(1.0f, 1.0f, 1.0f);
	m_angle    = 0.0f;

	LoadModel(path);
}

void Model::Draw(std::shared_ptr<Shader> shader)
{
	shader->Use();
	UpdateModelMatrix();
	shader->SetUniform("model", m_model);

	for (auto& mesh : m_meshes)
		mesh.Draw(shader);
	
	shader->Unuse();
}


void Model::Scale(const vf3& scale)
{
	m_scale += scale;
}

void Model::Rotate(const f32 angle, const vf3& axis)
{
	m_rotation += axis;
	m_angle    += angle;
}

void Model::Translate(const vf3& pos)
{
	m_position += pos;
}

void Model::UpdateModelMatrix()
{
	m_model = mf4x4(1.0f);

	// This somehow does not work, returns inf: can we make this work?
	//m_model = glm::rotate(m_model, glm::radians(m_angle), m_rotation);
	
	// This somehow does work, but 3 lines
	m_model = glm::rotate(m_model, glm::radians(m_rotation.x), { 1.0f, 0.0f, 0.0f });
	m_model = glm::rotate(m_model, glm::radians(m_rotation.y), { 0.0f, 1.0f, 0.0f });
	m_model = glm::rotate(m_model, glm::radians(m_rotation.z), { 0.0f, 0.0f, 1.0f });

	m_model = glm::translate(m_model, m_position);
	m_model = glm::scale(m_model, m_scale);
}

mf4x4 Model::GetModelMatrix() const
{
	return m_model;
}

std::vector<Mesh> Model::GetMeshes() const
{
	return m_meshes;
}

vf3 Model::GetPosition() const
{
	return m_position;
}

vf3 Model::GetRotation() const
{
	return m_rotation;
}

vf3 Model::GetScale() const
{
	return m_scale;
}

f32 Model::GetAngle() const
{
	return m_angle;
}

void Model::SetPosition(const vf3& pos)
{
	m_position = pos;
}

void Model::SetRotation(const vf3& axis)
{
	m_rotation = axis;
}

void Model::SetScale(const vf3& scale)
{
	m_scale = scale;
}

void Model::SetAngle(const f32 angle)
{
	m_angle = angle;
}

void Model::SetName(std::string name)
{
	m_name = name;
}

std::string Model::GetName()
{
	return m_name;
}

void Model::AddTexture(const std::shared_ptr<Texture>& texture)
{
	m_textures.push_back(texture);
}

std::vector<std::shared_ptr<Texture>> Model::GetTextures() const
{
	return m_textures;
}

void Model::LoadModel(const std::string& path)
{
	m_directory = path.substr(0, path.find_last_of('/'));

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (u32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (u32 i = 0; i < node->mNumChildren; i++)
		ProcessNode(node->mChildren[i], scene);
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices = ProcessVertices(mesh, scene);
	std::vector<u32> indices = ProcessIndices(mesh);
	std::vector<std::shared_ptr<Texture>> textures = ProcessMaterials(mesh, scene);

	m_meshes.push_back(Mesh(vertices, indices, textures));
}

std::vector<Vertex> Model::ProcessVertices(aiMesh* mesh, const aiScene* scene)
{
	 std::vector<Vertex> vertices;
	 for (u32 i = 0; i < mesh->mNumVertices; i++)
	 {
		Vertex vertex;

		// Position
		 if (mesh->HasPositions())
		 {
			 vertex.position = {
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z
			 };
		 }

		 // Normal
		 if (mesh->HasNormals())
		 {
			 vertex.normal = {
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			 };
		 }

		 // Texture
		 if (mesh->HasTextureCoords(0))
		 {
			 vertex.texcoords = {
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			 };
		 }
		 else
		 {
			 vertex.texcoords = { 0.0f, 0.0f };
		 }

		 // Color
		 if (mesh->HasVertexColors(0))
		 {
			 vertex.col = {
				 mesh->mColors[0][i].r,
				 mesh->mColors[0][i].g,
				 mesh->mColors[0][i].b,
				 mesh->mColors[0][i].a
			 };
		 }
		 else
		 {
			 vertex.col = { 1.0f, 1.0f, 1.0f, 1.0f };
		 }

		 if (mesh->HasTangentsAndBitangents())
		 {
			 // tangent
			 vertex.tangent = {
				 mesh->mTangents[i].x,
				 mesh->mTangents[i].y,
				 mesh->mTangents[i].z
			 };

			 // bitangent
  			 vertex.bitangent = {
				mesh->mBitangents[i].x,
				mesh->mBitangents[i].y,
				mesh->mBitangents[i].z
			 };
		 }

		 vertices.push_back(vertex);
	 }

	 return vertices;
}

std::vector<u32> Model::ProcessIndices(aiMesh* mesh)
{
	std::vector<u32> indices;
	for (u32 i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (u32 j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return indices;
}

std::vector<std::shared_ptr<Texture>> Model::ProcessMaterials(aiMesh* mesh, const aiScene* scene)
{
	std::vector<std::shared_ptr<Texture>> textures;
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<std::shared_ptr<Texture>> diffuses = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
	textures.insert(textures.end(), diffuses.begin(), diffuses.end());

	std::vector<std::shared_ptr<Texture>> speculars = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
	textures.insert(textures.end(), speculars.begin(), speculars.end());

	std::vector<std::shared_ptr<Texture>> normals = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
	textures.insert(textures.end(), normals.begin(), normals.end());

	return textures;
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType texture_type, std::string type_name)
{
	std::vector<std::shared_ptr<Texture>> textures;
	for (u32 i = 0; i < material->GetTextureCount(texture_type); i++)
	{
		aiString str;
		material->GetTexture(texture_type, i, &str);
		// check if texture it already exists in the textures vector
		bool skip = false;
		for (u32 j = 0; j < m_textures.size(); j++)
		{
			std::string tex_path = m_directory + "/" + str.C_Str();
			if (std::strcmp(m_textures[j]->GetPath().c_str(), tex_path.c_str()) == 0)
			{
				textures.push_back(m_textures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			textures.push_back(std::make_shared<Texture>(m_directory + "/" + str.C_Str(), type_name, true));
			m_textures.push_back(textures.back());
		}
	}

	return textures;
}