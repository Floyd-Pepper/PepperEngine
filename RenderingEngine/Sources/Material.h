#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Material(const glm::vec3& ambient = glm::vec3(0.2f, 0.2f, 0.2f), const glm::vec3& diffuse = glm::vec3(0.5f, 0.5f, 0.5f), const glm::vec3& specular = glm::vec3(1.0f, 1.0f, 1.0f), GLfloat shininess = 32);
	~Material();

	const glm::vec3& GetAmbient() const { return _Ambient; }
  const glm::vec3& GetDiffuse() const { return _Diffuse; }
  const glm::vec3& GetSpecular() const { return _Specular; }
  const GLfloat GetShininess() const { return _Shininess; }

private:
	glm::vec3 _Ambient;
	glm::vec3 _Diffuse;
	glm::vec3 _Specular;
	GLfloat _Shininess;
};
