#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& ambient = glm::vec3(0.3f, 0.3f, 0.3f), const glm::vec3& diffuse = glm::vec3(0.5f, 0.5f, 0.5f),const glm::vec3& specular = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec3& direction = glm::vec3(-0.2f, -1.0f, -0.3f));
	~DirectionalLight(){}

	void SetUniformValues(GLuint programID, unsigned int lightNumber);

	virtual void Abstract() {}
private:
	glm::vec3 _Direction;
};