#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight() {}
	PointLight(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f), GLfloat constant = 1.0f, GLfloat linear = 0.09f, GLfloat quadratic = 0.032f);
	~PointLight(){}

	void SetUniformValues(GLuint programID, unsigned int lightNumber);

	virtual void Abstract() {}
private:
	GLfloat _Constant;
	GLfloat _Linear;
	GLfloat _Quadratic;
};