#include "PointLight.h"
#include "EngineManager.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat constant, GLfloat linear, GLfloat quadratic) : Light(position, ambient, diffuse, specular), _Constant(constant), _Linear(linear), _Quadratic(quadratic)
{

}

void PointLight::SetUniformValues(GLuint programID, unsigned int lightNumber)
{
	Camera camera = EngineManager::Instance().GetCamera();
	GLint viewPosLoc = glGetUniformLocation(programID, "viewPos");
	glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("pointLights", "position", lightNumber).c_str()), _Position.x, _Position.y, _Position.z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("pointLights", "ambient", lightNumber).c_str()), _Ambient.x, _Ambient.y, _Ambient.z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("pointLights", "diffuse", lightNumber).c_str()), _Diffuse.x, _Diffuse.y, _Diffuse.z);
	glUniform3f(glGetUniformLocation(programID, GetUniformName("pointLights", "specular", lightNumber).c_str()), _Specular.x, _Specular.y, _Specular.z);
	glUniform1f(glGetUniformLocation(programID, GetUniformName("pointLights", "constant", lightNumber).c_str()), _Constant);
	glUniform1f(glGetUniformLocation(programID, GetUniformName("pointLights", "constant", lightNumber).c_str()), _Constant);
	glUniform1f(glGetUniformLocation(programID, GetUniformName("pointLights", "linear", lightNumber).c_str()), _Linear);
	glUniform1f(glGetUniformLocation(programID, GetUniformName("pointLights", "quadratic", lightNumber).c_str()), _Quadratic);
}