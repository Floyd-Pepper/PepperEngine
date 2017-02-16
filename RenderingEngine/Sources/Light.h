#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f));
	
	virtual void Abstract() = 0;

	const glm::vec3& GetPosition() { return _Position; }
	const glm::vec3& GetAmbient() { return _Ambient; }
	const glm::vec3& GetDiffuse() { return _Diffuse; }
	const glm::vec3& GetSpecular() { return _Specular; }

protected:
	glm::vec3 _Position;
	glm::vec3 _Ambient;
	glm::vec3 _Diffuse;
	glm::vec3 _Specular;
};