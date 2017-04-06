#include "PointLight.h"
#include "EngineManager.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, GLfloat constant, GLfloat linear, GLfloat quadratic) : Light(position, ambient, diffuse, specular), _Constant(constant), _Linear(linear), _Quadratic(quadratic)
{

}

void PointLight::SetUniformValues(GLuint programID, unsigned int lightNumber)
{
	Camera camera = EngineManager::Instance().GetCamera();
	GLint viewPosLoc = glGetUniformLocation(programID, "viewPos");
	std::string name;
	glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	
	GetUniformName(name, "pointLights", "position", lightNumber);
	glUniform3f(glGetUniformLocation(programID, name.c_str()), _Position.x, _Position.y, _Position.z);
	GetUniformName(name, "pointLights", "ambient", lightNumber);
	glUniform3f(glGetUniformLocation(programID, name.c_str()), _Ambient.x, _Ambient.y, _Ambient.z);
	GetUniformName(name, "pointLights", "diffuse", lightNumber);
	glUniform3f(glGetUniformLocation(programID, name.c_str()), _Diffuse.x, _Diffuse.y, _Diffuse.z);
	GetUniformName(name, "pointLights", "specular", lightNumber);
	glUniform3f(glGetUniformLocation(programID, name.c_str()), _Specular.x, _Specular.y, _Specular.z);
	GetUniformName(name, "pointLights", "constant", lightNumber);
	glUniform1f(glGetUniformLocation(programID, name.c_str()), _Constant);
	GetUniformName(name, "pointLights", "linear", lightNumber);
	glUniform1f(glGetUniformLocation(programID, name.c_str()), _Linear);
	GetUniformName(name, "pointLights", "quadratic", lightNumber);
	glUniform1f(glGetUniformLocation(programID, name.c_str()), _Quadratic);
}