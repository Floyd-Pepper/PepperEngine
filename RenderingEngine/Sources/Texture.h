#pragma once
#include <GL\glew.h>

class Texture {
public:
	enum WrappingMethod { Repeat, MirroredRepeat, ClampToEdge, ClampToBorder };
	enum FilteringMethod { Nearest, Linear };

	Texture() {}
	/*Texture(char* path);
	Texture(char* Path, WrappingMethod wrappingMethod);
	Texture(char* Path, FilteringMethod filteringMethod);*/
	Texture(char* Path, WrappingMethod wrappingMethod = Repeat, FilteringMethod filteringMethod = Linear);
	~Texture() {}

	void CreateTexture();

	const GLuint GetTextureID() const { return _Texture; }

private:
	void LoadTexture(char* path);
	void GenerateTexture();
	void SetWrappingParameters() const;
	void SetFilteringParameters() const;

private:
	GLuint _Texture;
	int _Width;
	int _Height;
	unsigned char* _Image;
	char* _Path;
	WrappingMethod _WrappingMethod;
	FilteringMethod _FilteringMethod;
};