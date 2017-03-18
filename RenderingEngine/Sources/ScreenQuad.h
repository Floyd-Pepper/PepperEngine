#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EngineManager.h"
#include "Framebuffer.h"

#include <string>

class ScreenQuad
{
public:
	ScreenQuad(const Framebuffer& framebuffer, const std::string& effectName = "PostProcessShader");
	~ScreenQuad();
	void Draw();

private:
	void Setup();

private:
	GLuint _VAO;
	Framebuffer _Framebuffer;
	Shader _EffectShader;
};