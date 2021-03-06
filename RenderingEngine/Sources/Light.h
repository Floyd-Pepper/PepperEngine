#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Light
{
public:
	Light(const glm::vec3& position = glm::vec3(0.0f,0.0f,0.0f), const glm::vec3& ambient = glm::vec3(0.2f, 0.2f, 0.2f), const glm::vec3& diffuse = glm::vec3(0.5f, 0.5f, 0.5f), const glm::vec3& specular = glm::vec3(1.0f, 1.0f, 1.0f));
	
	virtual void Abstract() = 0;

	const glm::vec3& GetPosition() const { return _Position; }
  const glm::vec3& GetAmbient() const { return _Ambient; }
  const glm::vec3& GetDiffuse() const { return _Diffuse; }
  const glm::vec3& GetSpecular() const { return _Specular; }

protected:
	void GetUniformName(std::string& name, const std::string& lightArrayName, const std::string& propertyName, unsigned int lightIndex);

protected:
	glm::vec3 _Position;
	glm::vec3 _Ambient;
	glm::vec3 _Diffuse;
	glm::vec3 _Specular;
};