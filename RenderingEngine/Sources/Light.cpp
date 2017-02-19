#include "Light.h"
#include "EngineManager.h"

#include <string>
#include <sstream>

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	_Position = position;
	_Ambient = ambient;
	_Diffuse = diffuse;
	_Specular = specular;
}

std::string Light::GetUniformName(const char* lightArrayName, const char* propertyName, size_t lightIndex) {
	std::ostringstream ss;
	ss << lightArrayName << "[" << lightIndex << "]." << propertyName;
	return ss.str();
}