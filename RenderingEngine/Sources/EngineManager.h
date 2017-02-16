#pragma once
#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Shader.h"

#include <map>

class EngineManager 
{
public:
	static EngineManager& Instance();

	void InitializeEngine();

	Camera& GetCamera() { return _Camera; }
	void SetCamera(const Camera& camera) { _Camera = camera; }

	DirectionalLight* GetDirectionalLight() { return _DirectionalLight; }
	void SetDirectionalLight(DirectionalLight* light) { _DirectionalLight = light; }

	PointLight* GetPointLight() { return _PointLight; }
	void SetPointLight(PointLight* light) { _PointLight = light; }

	const Shader& GetShaderByName(const std::string shaderName)
	{
		return _Shaders[shaderName];
	}

private:
	static EngineManager _Instance;
	Camera _Camera;

	DirectionalLight* _DirectionalLight;
	PointLight* _PointLight;
	std::map<std::string, Shader> _Shaders;

	EngineManager();
	~EngineManager() {}
};