// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <fstream>

#pragma once

// encapsulating class for shaders
class Shader
{
public:
	Shader() {}
	Shader(GLchar* vertexPath, GLchar* fragmentPath);
	~Shader() {}

	enum ShaderType { Vertex, Fragment };

	const char* GetShaderSource(const GLchar* path);
	void CompileShaderSource(const GLchar* sourceCode, ShaderType type);
	void CreateShaderProgram();
	void CreateShader();

	void Use() { glUseProgram(this->_Program); }

	const GLuint GetProgram() const { return _Program; }

private:
	GLuint _VertexShader;
	GLuint _FragmentShader;
	GLuint _Program;
	GLchar* _VertexPath;
	GLchar* _FragmentPath;	
};