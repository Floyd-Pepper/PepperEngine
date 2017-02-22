#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

#include <vector>

class Model
{
public:
	Model(GLchar* path)
	{
		this->LoadModel(path);
	}
	void Draw(LightingModel lightingModel);

	void SetMaterial(const Material& material);
	void Translate(glm::vec3 translationVector);
	void Rotate(GLfloat angle, glm::vec3 rotationAxis);
	void Scale(glm::vec3 scale);

private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

private:
	std::vector<Mesh> _Meshes;
	std::string _Directory;
	std::vector<Texture> _TexturesLoaded;
};