#include "Material.h"

Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, GLfloat shininess)
{
	_Ambient = ambient;
	_Diffuse = diffuse;
	_Specular = specular;
	_Shininess = shininess;
}

Material::~Material()
{
}
