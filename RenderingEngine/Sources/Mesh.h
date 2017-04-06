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

enum Topology
{
	POINTS,
	LINES,
	LINE_STRIP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
};

class Mesh
{
public:
	Mesh() {}
  Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures);
  Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Shader& shader, const Material& material = Material());
	~Mesh() {}

	void FillDataStructure(const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& UV, const std::vector<glm::vec3>& normals);
	void FillDataStructure(const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& UV, const std::vector<glm::vec3>& normals, const std::vector<int>& indices);
	virtual void ConfigureMesh();
	void ConfigureMeshIndices(); // a supprimer ?
	//virtual void Draw();
	void Draw(LightingModel lightingModel);
	void SetTexturesUniformValues();
	void SetMvpUniformValue();
	void SetMaterialUniformValues();
	void SetColorUniformValues();
	void DrawIndices(); // à supprimer ?

	void AddTexture(Texture& texture);

	void SetObjectColor(const glm::vec3& color);

	//transformations :
	void Translate(const glm::vec3& translationVector);
	void Rotate(GLfloat angle, const glm::vec3& rotationAxis);
	void Scale(const glm::vec3& scaleValues);

	const Shader& GetShader() const { return _Shader; }
	void SetShader(Shader& shader) { _Shader = shader; }

	const Material& GetMaterial() const { return _Material; }
	void SetMaterial(const Material& material) { _Material = material; }

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
	Topology _Topology = TRIANGLES;
};