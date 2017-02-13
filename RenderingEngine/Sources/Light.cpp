#include "Light.h"
#include "EngineManager.h"

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	_Position = position;
	_Ambient = ambient;
	_Diffuse = diffuse;
	_Specular = specular;
	EngineManager::Instance().SetLight(*this);
}
