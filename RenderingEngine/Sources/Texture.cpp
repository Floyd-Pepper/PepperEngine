#include <SOIL\SOIL.h>
#include "Texture.h"

Texture::Texture(const char * path, TextureType type, WrappingMethod wrappingMethod, FilteringMethod filteringMethod) : _Path(path), _WrappingMethod(wrappingMethod), _FilteringMethod(filteringMethod)
{
	SetType(type);
	CreateTexture();
}

void Texture::CreateTexture()
{
	LoadTexture(_Path.c_str());
	GenerateTexture();
}

void Texture::SetType(TextureType type)
{
	switch (type) 
	{
	case IMAGE:
		_Type = "texture_image";
		break;
	case SPECULAR:
		_Type = "texture_specular";
		break;
	case DIFFUSE:
		_Type = "texture_diffuse";
		break;
	}
}

void Texture::LoadTexture(const char* path)
{
	_Image = SOIL_load_image(path, &_Width, &_Height, 0, SOIL_LOAD_RGB);
}

void Texture::GenerateTexture()
{
	glGenTextures(1, &_Id);
	glBindTexture(GL_TEXTURE_2D, _Id);
	
	SetWrappingParameters();
	SetFilteringParameters();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _Width, _Height, 0, GL_RGB, GL_UNSIGNED_BYTE, _Image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(_Image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetWrappingParameters() const
{
	switch (_WrappingMethod) {
	case Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case MirroredRepeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	case ClampToEdge:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case ClampToBorder:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		break;
	}	
}

void Texture::SetFilteringParameters() const
{
	switch (_FilteringMethod)
	{
	case Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
}
