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
	// lighting shaders
	Shader colorShader("../RenderingEngine/Sources/Shaders/Color_Only.vs", "../RenderingEngine/Sources/Shaders/Color_Only.fs");
	_Shaders["ColorOnly"] = colorShader;
	Shader BlinnPhongShader("../RenderingEngine/Sources/Shaders/Standard_Lighting.vs", "../RenderingEngine/Sources/Shaders/Standard_Lighting.fs");
	_Shaders["BlinnPhongShader"] = BlinnPhongShader;
	Shader skyboxShader("../RenderingEngine/Sources/Shaders/Skybox.vs", "../RenderingEngine/Sources/Shaders/Skybox.fs");
	_Shaders["SkyboxShader"] = skyboxShader;
	GLchar* screenQuadVertexShader = "../RenderingEngine/Sources/Shaders/ScreenQuad.vs";
	Shader postProcessShader(screenQuadVertexShader, "../RenderingEngine/Sources/Shaders/DefaultPostProcess.fs");
	_Shaders["PostProcessShader"] = postProcessShader;
	// effect shaders
	Shader inversionShader(screenQuadVertexShader, "../RenderingEngine/Sources/Shaders/InversionEffect.fs");
	_Shaders["InversionEffect"] = inversionShader;
	Shader grayscaleShader(screenQuadVertexShader, "../RenderingEngine/Sources/Shaders/GrayscaleEffect.fs");
	_Shaders["GrayscaleEffect"] = grayscaleShader;
	Shader blurShader(screenQuadVertexShader, "../RenderingEngine/Sources/Shaders/BlurEffect.fs");
	_Shaders["BlurEffect"] = blurShader;
	Shader edgeDetectionShader(screenQuadVertexShader, "../RenderingEngine/Sources/Shaders/EdgeDetectionEffect.fs");
	_Shaders["EdgeDetectionEffect"] = edgeDetectionShader;
}

const Shader & EngineManager::GetShaderByName(const std::string& shaderName)
{
	return _Shaders[shaderName];
}

