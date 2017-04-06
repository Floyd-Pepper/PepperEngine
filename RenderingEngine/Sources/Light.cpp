#include "Light.h"
#include "EngineManager.h"

#include <string>
#include <sstream>

Light::Light(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
{
	_Position = position;
	_Ambient = ambient;
	_Diffuse = diffuse;
	_Specular = specular;
}

void Light::GetUniformName(std::string& name, const std::string& lightArrayName, const std::string& propertyName, unsigned int lightIndex) {
	//std::ostringstream ss;
	//ss << lightArrayName << "[" << lightIndex << "]." << propertyName;
	name = lightArrayName + "[" + std::to_string(lightIndex) + "]." + propertyName;
	//return ss.str();
}