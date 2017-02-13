#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess)
{
	_Ambient = ambient;
	_Diffuse = diffuse;
	_Specular = specular;
	_Shininess = shininess;
}

Material::~Material()
{
}
