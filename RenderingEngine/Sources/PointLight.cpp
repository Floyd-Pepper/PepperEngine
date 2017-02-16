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
	glUniform3f(glGetUniformLocation(programID, "pointLights.position"), _Position.x, _Position.y, _Position.z);
	glUniform3f(glGetUniformLocation(programID, "pointLights.ambient"), _Ambient.x, _Ambient.y, _Ambient.z);
	glUniform3f(glGetUniformLocation(programID, "pointLights.diffuse"), _Diffuse.x, _Diffuse.y, _Diffuse.z);
	glUniform3f(glGetUniformLocation(programID, "pointLights.specular"), _Specular.x, _Specular.y, _Specular.z);
	glUniform1f(glGetUniformLocation(programID, "pointLights.constant"), _Constant);
	glUniform1f(glGetUniformLocation(programID, "pointLights.linear"), _Linear);
	glUniform1f(glGetUniformLocation(programID, "pointLights.quadratic"), _Quadratic);
}
