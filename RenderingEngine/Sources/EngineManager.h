#pragma once
#include "Camera.h"
#include "Light.h"

class EngineManager 
{
public:
	static EngineManager& Instance();

	Camera& GetCamera() { return _Camera; }
	void SetCamera(const Camera& camera) { _Camera = camera; }

	const Light& GetLight() { return _Light; }
	void SetLight(const Light& light) { _Light = light; }

private:
	static EngineManager _Instance;
	Camera _Camera;
	Light _Light;

	EngineManager();
	~EngineManager() {}
};