#pragma once
#include "Camera.h"
#include "Light.h"
#include "Shader.h"

#include <map>

class EngineManager 
{
public:
	static EngineManager& Instance();

	void InitializeEngine();

	Camera& GetCamera() { return _Camera; }
	void SetCamera(const Camera& camera) { _Camera = camera; }

	const Light& GetLight() { return _Light; }
	void SetLight(const Light& light) { _Light = light; }

	const Shader& GetShaderByName(const std::string shaderName)
	{
		return _Shaders[shaderName];
	}

private:
	static EngineManager _Instance;
	Camera _Camera;
	Light _Light;
	std::map<std::string, Shader> _Shaders;

	EngineManager();
	~EngineManager() {}
};