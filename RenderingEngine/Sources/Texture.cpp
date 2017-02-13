#include <SOIL\SOIL.h>
#include "Texture.h"

/*Texture::Texture(char* path) : _Path(path)
{
	_WrappingMethod = Repeat;
	_FilteringMethod = Linear;
	CreateTexture();
}

Texture::Texture(char * path, WrappingMethod wrappingMethod) : _Path(path)
{
	_WrappingMethod = wrappingMethod;
	_FilteringMethod = Linear;
	CreateTexture();
}

Texture::Texture(char * path, FilteringMethod filteringMethod) : _Path(path)
{
	_WrappingMethod = Repeat;
	_FilteringMethod = filteringMethod;
	CreateTexture();
}

Texture::Texture(char * path, WrappingMethod wrappingMethod, FilteringMethod filteringMethod) : _Path(path)
{
	_WrappingMethod = wrappingMethod;
	_FilteringMethod = filteringMethod;
	CreateTexture();
}*/

Texture::Texture(char * path, WrappingMethod wrappingMethod, FilteringMethod filteringMethod) : _Path(path), _WrappingMethod(wrappingMethod), _FilteringMethod(filteringMethod)
{
	CreateTexture();
}

void Texture::CreateTexture()
{
	LoadTexture(_Path);
	GenerateTexture();
}

void Texture::LoadTexture(char* path)
{
	_Image = SOIL_load_image(path, &_Width, &_Height, 0, SOIL_LOAD_RGB);
}

void Texture::GenerateTexture()
{
	glGenTextures(1, &_Texture);
	glBindTexture(GL_TEXTURE_2D, _Texture);
	
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
