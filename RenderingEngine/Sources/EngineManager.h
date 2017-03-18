#pragma once
#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Shader.h"

#include <map>
#include <vector>

class EngineManager 
{
public:
	static EngineManager& Instance();

	void InitializeEngine();

	void SetLightUniformValues();

	Camera& GetCamera() { return _Camera; }
	void SetCamera(const Camera& camera) { _Camera = camera; }

	const std::vector<PointLight>& GetPointLights() { return _PointLights; }
	void AddPointLight(const PointLight& light) { _PointLights.push_back(light); }
	const std::vector<DirectionalLight>& GetDirectionalLights() { return _DirectionalLights; }
	void AddDirectionalLight(const DirectionalLight& light) { _DirectionalLights.push_back(light); }

	const Shader& GetShaderByName(const std::string shaderName);

private:
	static EngineManager _Instance;
	Camera _Camera;

	std::map<std::string, Shader> _Shaders;
	std::vector<PointLight> _PointLights;
	std::vector<DirectionalLight> _DirectionalLights;

	EngineManager();
	~EngineManager() {}
};