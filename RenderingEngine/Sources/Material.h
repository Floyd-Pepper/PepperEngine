#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Material(glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f), GLfloat shininess = 32);
	~Material();

	const glm::vec3& GetAmbient(){ return _Ambient; }
	const glm::vec3& GetDiffuse() { return _Diffuse; }
	const glm::vec3& GetSpecular() { return _Specular; }
	const GLfloat GetShininess() { return _Shininess; }

private:
	glm::vec3 _Ambient;
	glm::vec3 _Diffuse;
	glm::vec3 _Specular;
	GLfloat _Shininess;
};
