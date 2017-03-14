#pragma once
#include "Cube.h"
#include "Shader.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Skybox
{
public:
	Skybox();
	~Skybox() {}
	void ConfigureSkybox();
	void loadCubemap(std::vector<const GLchar*> faces);
	void Draw();

private:
	GLuint _SkyboxVAO;
	GLuint _TextureId;
	Cube _CubeMesh;
};
