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
