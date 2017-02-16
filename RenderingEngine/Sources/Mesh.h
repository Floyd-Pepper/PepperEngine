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

class Mesh
{
public:
	Mesh() {}
	Mesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, Shader& shader, Material& material = Material());
	~Mesh() {}

	virtual void ConfigureMesh();
	void ConfigureMeshIndices(); // a supprimer ?
	virtual void Draw();
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

	const Texture& GetSpecularMap() const { return *_SpecularMap; }
	void SetSpecularMap(Texture& texture) { _SpecularMap = &texture; }

protected:
	GLuint _VAO;
	std::vector<GLfloat> _Vertices;
	std::vector<GLuint> _Indices; // a supprimer ?
	GLint _VerticesNumber;

	glm::mat4 _Transformation;

	std::vector <std::shared_ptr<Texture>> _Textures;
	Texture* _SpecularMap = nullptr;
	Material _Material;
	glm::vec3 _ObjectColor = glm::vec3(1.0f,1.0f,1.0f);
	Shader _Shader;

	LightingModel _LightingModel;
};