#pragma once
#include <GL\glew.h>

#include <string>

class Texture {
public:
	enum WrappingMethod { Repeat, MirroredRepeat, ClampToEdge, ClampToBorder };
	enum FilteringMethod { Nearest, Linear };
	enum TextureType { IMAGE, SPECULAR, DIFFUSE };

	Texture() {}
	/*Texture(char* path);
	Texture(char* Path, WrappingMethod wrappingMethod);
	Texture(char* Path, FilteringMethod filteringMethod);*/
	Texture(const char* Path, TextureType type = IMAGE, WrappingMethod wrappingMethod = Repeat, FilteringMethod filteringMethod = Linear);
	~Texture() {}

	void CreateTexture();

	const GLuint GetTextureID() const { return _Id; }
	void SetTextureID(GLuint id) { _Id = id; }

	const std::string& GetType() const { return _Type; }
	void SetType(TextureType type);
	void SetStringType(const std::string& type) { _Type = type; }

	const std::string& GetPath() const { return _Path; }
	void SetPath(const std::string& path) { _Path = path; }

private:
	void LoadTexture(const char* path);
	void GenerateTexture();
	void SetWrappingParameters() const;
	void SetFilteringParameters() const;

private:
	GLuint _Id;
	std::string _Type;
	int _Width;
	int _Height;
	unsigned char* _Image;
	std::string _Path;
	WrappingMethod _WrappingMethod;
	FilteringMethod _FilteringMethod;
};