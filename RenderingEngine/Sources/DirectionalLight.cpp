#include "DirectionalLight.h"
#include "EngineManager.h"

DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction) : Light(position, ambient, diffuse, specular), _Direction(direction)
{

}

void DirectionalLight::SetUniformValues(GLuint programID, unsigned int lightNumber)
{
	Camera camera = EngineManager::Instance().GetCamera();
	GLint viewPosLoc = glGetUniformLocation(programID, "viewPos");
	glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("dirLights", "direction", lightNumber).c_str()), _Direction.x, _Direction.y, _Direction.z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("dirLights", "ambient", lightNumber).c_str()), _Ambient.x, _Ambient.y, _Ambient.z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("dirLights", "diffuse", lightNumber).c_str()), _Diffuse.x, _Diffuse.y, _Diffuse.z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("dirLights", "specular", lightNumber).c_str()), _Specular.x, _Specular.y, _Specular.z);
}
