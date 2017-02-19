#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Defs.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
public:
	Mesh() {}
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Shader& shader, Material& material = Material());	
	~Mesh() {}

	void FillDataStructure(std::vector<glm::vec3> positions, std::vector<glm::vec2> UV, std::vector<glm::vec3> normals);
	virtual void ConfigureMesh();
	void ConfigureMeshIndices(); // a supprimer ?
	//virtual void Draw();
	void Draw(LightingModel lightingModel);
	void SetTexturesUniformValues();
	void SetMvpUniformValue();
	void SetMaterialUniformValues();
	//void SetPhongLightingUniformValues();
	void SetColorUniformValues();
	void DrawIndices(); // à supprimer ?

	void AddTexture(Texture& texture);

	void SetObjectColor(glm::vec3 color);

	//transformations :
	void Translate(glm::vec3 translationVector);
	void Rotate(GLfloat angle, glm::vec3 rotationAxis);
	void Scale(glm::vec3 scaleValues);

	const Shader& GetShader() const { return _Shader; }
	void SetShader(Shader& shader) { _Shader = shader; }

	const Material& GetMaterial() const { return _Material; }
	void SetMaterial(Material& material) { _Material = material; }

protected:
	GLuint _VAO;
	std::vector<Vertex> _Vertices;
	std::vector<GLuint> _Indices;
	GLint _VerticesNumber;

	glm::mat4 _Transformation;

	std::vector<Texture> _Textures;
	Material _Material;
	glm::vec3 _ObjectColor = glm::vec3(1.0f,1.0f,1.0f);
	Shader _Shader;

	LightingModel _LightingModel;
};