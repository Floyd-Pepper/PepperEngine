#include "Shader.h"
#include <sstream>
#include <string.h>

Shader::Shader(GLchar* vertexPath, GLchar* fragmentPath) : _VertexPath(vertexPath), _FragmentPath(fragmentPath)
{
	CreateShader();
}

const GLchar* Shader::GetShaderSource(const GLchar* path)
{
	std::string code;
	std::ifstream shaderFile;
	// ensures ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shaderFile.open(path);
		std::stringstream shaderStream;
		// Read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file
		shaderFile.close();
		code = shaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	char * shaderCode = new char[code.length() + 1];
	memcpy(shaderCode, code.c_str(), code.size() + 1);
	return shaderCode;
}

void Shader::CompileShaderSource(const GLchar* sourceCode, ShaderType type)
{
	GLuint shader;
	GLint success;
	GLchar infoLog[512];

	if(type == Vertex)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if(type == Fragment)
		shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shader, 1, &sourceCode, nullptr);
	glCompileShader(shader);
	// Print compile errors if any
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		if (type == Vertex)
			_VertexShader = shader;
		else if (type == Fragment)
			_FragmentShader = shader;
	}
}

void Shader::CreateShaderProgram()
{
	// Shader Program
	_Program = glCreateProgram();
	glAttachShader(_Program, _VertexShader);
	glAttachShader(_Program, _FragmentShader);
	glLinkProgram(_Program);

	GLint success;
	GLchar infoLog[512];
	// Print linking errors if any
	glGetProgramiv(_Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_Program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		glDeleteProgram(_Program);
	}
	// Delete the shaders as they're linked the program now and no longer necessery
	glDeleteShader(_VertexShader);
	glDeleteShader(_FragmentShader);
}

void Shader::CreateShader()
{
	const GLchar* vertexSourceCode = GetShaderSource(_VertexPath);
	const GLchar* fragmentSourceCode = GetShaderSource(_FragmentPath);
	CompileShaderSource(vertexSourceCode, ShaderType::Vertex);
	CompileShaderSource(fragmentSourceCode, ShaderType::Fragment);
	CreateShaderProgram();
}
