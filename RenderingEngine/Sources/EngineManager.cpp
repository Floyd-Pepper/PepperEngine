#include "EngineManager.h"

EngineManager EngineManager::_Instance = EngineManager();

EngineManager::EngineManager() {
	_Camera = Camera();
}

EngineManager& EngineManager::Instance()
{
	return _Instance;
}

void EngineManager::InitializeEngine()
{
	//Shader PhongColorShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\VertexShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\FragmentShader.fs");
	Shader PhongColorShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\PhongColorShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\PhongColorShader.fs");
	_Shaders["PhongColorShader"] = PhongColorShader;
	//Shader PhongTextureShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\TextureShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\TextureShader.fs");
	Shader PhongTextureShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\PhongTextureShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\PhongTextureShader.fs");
	_Shaders["PhongTextureShader"] = PhongTextureShader;
	Shader colorShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\ColorOnlyShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\ColorOnlyShader.fs");
	_Shaders["ColorShader"] = colorShader;
}

void EngineManager::SetLightUniformValues()
{
	Shader phongColorShader = GetShaderByName("PhongColorShader");
	phongColorShader.Use();
	GLint dirLightCount = glGetUniformLocation(phongColorShader.GetProgram(), "dirLightCount");
	GLint pointLightCount = glGetUniformLocation(phongColorShader.GetProgram(), "pointLightCount");
	glUniform1i(dirLightCount, GetDirectionalLights().size());
	glUniform1i(pointLightCount, GetPointLights().size());
	int lightNumber = 0;
	for (auto pointLight : GetPointLights())
	{
		pointLight.SetUniformValues(phongColorShader.GetProgram(), lightNumber);
		++lightNumber;
	}
	lightNumber = 0;
	for (auto directionalLight : GetDirectionalLights())
	{
		directionalLight.SetUniformValues(phongColorShader.GetProgram(), lightNumber);
		++lightNumber;
	}
	Shader phongTextureShader = GetShaderByName("PhongTextureShader");
	phongTextureShader.Use();
	dirLightCount = glGetUniformLocation(phongTextureShader.GetProgram(), "dirLightCount");
	pointLightCount = glGetUniformLocation(phongTextureShader.GetProgram(), "pointLightCount");
	glUniform1i(dirLightCount, GetDirectionalLights().size());
	glUniform1i(pointLightCount, GetPointLights().size());
	lightNumber = 0;
	for (auto pointLight : GetPointLights())
	{
		pointLight.SetUniformValues(phongTextureShader.GetProgram(), lightNumber);
		++lightNumber;
	}
	lightNumber = 0;
	for (auto directionalLight : GetDirectionalLights())
	{
		directionalLight.SetUniformValues(phongTextureShader.GetProgram(), lightNumber);
		++lightNumber;
	}
}
