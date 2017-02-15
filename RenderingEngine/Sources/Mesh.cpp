#include "Mesh.h"
#include "EngineManager.h"
#include "Camera.h"
#include "Light.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

Mesh::Mesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, Shader& shader, Material& material) : _Shader(shader), _Material(material)
{
	_Vertices = vertices;
	_Indices = indices;
	_Transformation = glm::mat4();
	ConfigureMesh();
}

void Mesh::ConfigureMesh()
{
	_Transformation = glm::mat4();

	glGenVertexArrays(1, &_VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _Vertices.size() * sizeof(GLfloat), &_Vertices[0], GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0); // Unbind VAO
}

void Mesh::ConfigureMeshIndices()
{
	glGenVertexArrays(1, &_VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	GLuint EBO;
	glGenBuffers(1, &EBO);
	// 1. Bind Vertex Array Object
	glBindVertexArray(_VAO);
	// 2. Copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _Vertices.size() * sizeof(GLfloat), &_Vertices[0], GL_STATIC_DRAW);
	// 3. Copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Indices.size() * sizeof(GLuint), &_Indices[0], GL_STATIC_DRAW);
	// 3. Then set the vertex attributes pointers
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// 4. Unbind VAO (NOT the EBO)
	glBindVertexArray(0);
}

void Mesh::Draw()
{
	// textures
	/*int i = 0;
	for (const auto& texture : _Textures)
	{
		GLuint in = texture->GetTextureID();
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		std::string strName = "texture" + std::to_string(i);
		const GLchar* textureName = strName.c_str();
		glUniform1i(glGetUniformLocation(_Shader.GetProgram(), textureName), i);
		i++;
	}*/
	int i = 0;
	for (const auto& texture : _Textures)
	{
		GLuint in = texture->GetTextureID();
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		//std::string strName = "texture" + std::to_string(i);
		//const GLchar* textureName = strName.c_str();
		glUniform1i(glGetUniformLocation(_Shader.GetProgram(), "material.diffuse"), i);
		i++;
	}
	/*if (nullptr != _SpecularMap)
	{
		GLuint in = _SpecularMap->GetTextureID();
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _SpecularMap->GetTextureID());
		glUniform1i(glGetUniformLocation(_Shader.GetProgram(), "material.specularMap"), i);
	}*/

	//activate shader
	_Shader.Use();

	//transformations (MVP)
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	model = _Transformation;
	// Camera / View transformation
	Camera camera = EngineManager::Instance().GetCamera();
	view = camera.GetViewMatrix();

	// projection
	projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

	// MVP matrix loc
	GLint modelLoc = glGetUniformLocation(_Shader.GetProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	GLint viewLoc = glGetUniformLocation(_Shader.GetProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	GLint projectionLoc = glGetUniformLocation(_Shader.GetProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
	//color & lightning
	GLint objectColorLoc = glGetUniformLocation(_Shader.GetProgram(), "objectColor");
	glUniform3f(objectColorLoc, _ObjectColor.x, _ObjectColor.y, _ObjectColor.z);
	GLint viewPosLoc = glGetUniformLocation(_Shader.GetProgram(), "viewPos");
	glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	GLint lightPosLoc = glGetUniformLocation(_Shader.GetProgram(), "light.position");
	GLint lightAmbientLoc = glGetUniformLocation(_Shader.GetProgram(), "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(_Shader.GetProgram(), "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(_Shader.GetProgram(), "light.specular");
	Light light = EngineManager::Instance().GetLight();
	glm::vec3 lightPosition = light.GetPosition();
	glUniform3f(lightPosLoc, lightPosition.x, lightPosition.y, lightPosition.z);
	glm::vec3 lightAmbient = light.GetAmbient();
	glUniform3f(lightAmbientLoc, lightAmbient.x, lightAmbient.y, lightAmbient.z);
	glm::vec3 lightDiffuse = light.GetDiffuse();
	glUniform3f(lightDiffuseLoc, lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
	glm::vec3 lightSpecular = light.GetSpecular();
	glUniform3f(lightSpecularLoc, lightSpecular.x, lightSpecular.y, lightSpecular.z);

	// material
	GLint matAmbientLoc = glGetUniformLocation(_Shader.GetProgram(), "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(_Shader.GetProgram(), "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(_Shader.GetProgram(), "material.specular");
	GLint matShineLoc = glGetUniformLocation(_Shader.GetProgram(), "material.shininess");
	glUniform3f(matAmbientLoc, _Material.GetAmbient().x, _Material.GetAmbient().y, _Material.GetAmbient().z);
	glUniform3f(matDiffuseLoc, _Material.GetDiffuse().x, _Material.GetDiffuse().y, _Material.GetDiffuse().z);
	glUniform3f(matSpecularLoc, _Material.GetSpecular().x, _Material.GetSpecular().y, _Material.GetSpecular().z);
	glUniform1f(matShineLoc, _Material.GetShininess());

	//Drawing
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, _VerticesNumber);
	glBindVertexArray(0);

	// reinitialization of the transformation matrix
	_Transformation = glm::mat4();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::Draw(LightingModel lightingModel)
{
	if (!_Textures.empty())
	{
		SetTexturesUniformValues();
	}
	switch (lightingModel)
	{
	case LightingModel::PHONG_COLOR:
		_Shader = EngineManager::Instance().GetShaderByName("PhongColorShader");
		_Shader.Use();
		SetPhongLightingUniformValues();
		break;
	case LightingModel::PHONG_TEXTURE:
		_Shader = EngineManager::Instance().GetShaderByName("PhongTextureShader");
		_Shader.Use();
		SetPhongLightingUniformValues();
		break;
	case LightingModel::DIFFUSE_ONLY:
		break;
	case LightingModel::COLOR_ONLY:
		_Shader = EngineManager::Instance().GetShaderByName("ColorShader");
		_Shader.Use();
		SetColorUniformValues();
		break;
	}
	SetMvpUniformValue();
	//Drawing
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, _VerticesNumber);
	glBindVertexArray(0);

	// reinitialization of the transformation matrix
	_Transformation = glm::mat4();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::SetTexturesUniformValues()
{
	int i = 0;
	for (const auto& texture : _Textures)
	{
		GLuint in = texture->GetTextureID();
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		//std::string strName = "texture" + std::to_string(i);
		//const GLchar* textureName = strName.c_str();
		glUniform1i(glGetUniformLocation(_Shader.GetProgram(), "material.diffuse"), i);
		i++;
	}
}

void Mesh::SetMvpUniformValue()
{
	//transformations (MVP)
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	model = _Transformation;
	// Camera / View transformation
	Camera camera = EngineManager::Instance().GetCamera();
	view = camera.GetViewMatrix();
	// projection
	projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	// MVP matrix loc
	GLint modelLoc = glGetUniformLocation(_Shader.GetProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	GLint viewLoc = glGetUniformLocation(_Shader.GetProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	GLint projectionLoc = glGetUniformLocation(_Shader.GetProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Mesh::SetPhongLightingUniformValues()
{
	Camera camera = EngineManager::Instance().GetCamera();
	//color & lightning
	GLint viewPosLoc = glGetUniformLocation(_Shader.GetProgram(), "viewPos");
	glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	GLint lightPosLoc = glGetUniformLocation(_Shader.GetProgram(), "light.position");
	GLint lightAmbientLoc = glGetUniformLocation(_Shader.GetProgram(), "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(_Shader.GetProgram(), "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(_Shader.GetProgram(), "light.specular");
	Light light = EngineManager::Instance().GetLight();
	glm::vec3 lightPosition = light.GetPosition();
	glUniform3f(lightPosLoc, lightPosition.x, lightPosition.y, lightPosition.z);
	glm::vec3 lightAmbient = light.GetAmbient();
	glUniform3f(lightAmbientLoc, lightAmbient.x, lightAmbient.y, lightAmbient.z);
	glm::vec3 lightDiffuse = light.GetDiffuse();
	glUniform3f(lightDiffuseLoc, lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
	glm::vec3 lightSpecular = light.GetSpecular();
	glUniform3f(lightSpecularLoc, lightSpecular.x, lightSpecular.y, lightSpecular.z);

	// material
	GLint matAmbientLoc = glGetUniformLocation(_Shader.GetProgram(), "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(_Shader.GetProgram(), "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(_Shader.GetProgram(), "material.specular");
	GLint matShineLoc = glGetUniformLocation(_Shader.GetProgram(), "material.shininess");
	glUniform3f(matAmbientLoc, _Material.GetAmbient().x, _Material.GetAmbient().y, _Material.GetAmbient().z);
	glUniform3f(matDiffuseLoc, _Material.GetDiffuse().x, _Material.GetDiffuse().y, _Material.GetDiffuse().z);
	glUniform3f(matSpecularLoc, _Material.GetSpecular().x, _Material.GetSpecular().y, _Material.GetSpecular().z);
	glUniform1f(matShineLoc, _Material.GetShininess());
}

void Mesh::SetColorUniformValues()
{
	GLint objectColorLoc = glGetUniformLocation(_Shader.GetProgram(), "objectColor");
	glUniform3f(objectColorLoc, _ObjectColor.x, _ObjectColor.y, _ObjectColor.z);
}

void Mesh::DrawIndices()
{
	// textures
	int i = 0;
	for (const auto& texture : _Textures)
	{
		GLuint in = texture->GetTextureID();
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		std::string strName = "texture" + std::to_string(i);
		const GLchar* textureName = strName.c_str();
		glUniform1i(glGetUniformLocation(_Shader.GetProgram(), textureName), i);
		i++;
	}
	//activate shader
	_Shader.Use();

	//transformations (MVP)
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 MVP = projection * view * model;
	GLint MVPLoc = glGetUniformLocation(_Shader.GetProgram(), "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	GLuint transformLoc = glGetUniformLocation(_Shader.GetProgram(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(_Transformation));

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	// reinitialization of the transformation matrix
	_Transformation = glm::mat4();
}

void Mesh::AddTexture(Texture& texture)
{
	_Textures.push_back(std::make_shared<Texture>(texture));
}

void Mesh::SetObjectColor(glm::vec3 color)
{
	_ObjectColor = color;
}

void Mesh::Translate(glm::vec3 translationVector)
{
	_Transformation = glm::translate(_Transformation, translationVector);
}

void Mesh::Rotate(GLfloat angle, glm::vec3 rotationAxis)
{
	_Transformation = glm::rotate(_Transformation, angle, rotationAxis);
}

void Mesh::Scale(glm::vec3 scaleValues)
{
	_Transformation = glm::scale(_Transformation, scaleValues);
}