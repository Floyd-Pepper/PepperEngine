#include "ScreenQuad.h"

ScreenQuad::ScreenQuad(const Framebuffer & framebuffer, const std::string & effectName) : _Framebuffer(framebuffer)
{
	_EffectShader = EngineManager::Instance().GetShaderByName(effectName);
	Setup();
}

ScreenQuad::~ScreenQuad()
{
}

void ScreenQuad::Setup()
{
	GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
								 // Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	GLuint VBO;
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void ScreenQuad::Draw()
{
	// Bind again default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	// Draw Screen
	_EffectShader.Use();
	glBindVertexArray(_VAO);
	GLuint debug = _Framebuffer.GetTextureID();
	glBindTexture(GL_TEXTURE_2D, _Framebuffer.GetTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
