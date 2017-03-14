// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EngineManager.h"
#include "WindowManager.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Texture.h"
#include "Mesh.h"
#include "Cube.h"
#include "Plane.h"
#include "Model.h"
#include "Skybox.h"

#include "Defs.h"

#include <iostream>

int main()
{
	WindowManager windowManager(1920, 1080);
	EngineManager::Instance().InitializeEngine();

	std::vector<GLfloat> vertices = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // Top Left 
	};

	std::vector<GLuint> indices = {  // Note that we start from 0!
		0, 1, 2,
		0, 2, 3
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

 	DirectionalLight dirLight(glm::vec3(1.0f,1.0f,1.0f));
	EngineManager::Instance().AddDirectionalLight(dirLight);
	PointLight pointLight(glm::vec3(2.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.1f, 0.1f, 1.0f), glm::vec3(0.1f, 0.1f, 1.0f), 1.0f, 0.045f,  0.0075f);
	EngineManager::Instance().AddPointLight(pointLight);
	PointLight pointLight2(glm::vec3(-2.0f, 3.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.9f, 0.9f, 0.0f), glm::vec3(0.9f, 0.9f, 0.0f));
	EngineManager::Instance().AddPointLight(pointLight2);
	/*PointLight pointLight(glm::vec3(1.0f, 1.0f, 1.0f));
	EngineManager::Instance().AddPointLight(pointLight);
	PointLight pointLight2(glm::vec3(-2.0f, 3.0f, -2.0f));
	EngineManager::Instance().AddPointLight(pointLight2);*/

	Texture texture1("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\container.jpg", Texture::DIFFUSE, Texture::MirroredRepeat, Texture::Nearest);
	Texture texture2("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\awesomeface.png", Texture::IMAGE, Texture::MirroredRepeat, Texture::Nearest);
	Texture containerTexture("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\container2.png", Texture::DIFFUSE);
	Texture containerSpecularMap("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\container2_specular.png", Texture::SPECULAR);
	Texture parquet("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\parquet.png", Texture::DIFFUSE);
	Texture brickwallTexture("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\brickwall.jpg", Texture::DIFFUSE);
	//Texture woodTexture("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\wood.jpg", Texture::DIFFUSE);
	Texture chairTexture("C:/Users/Julien/Documents/Visual Studio 2015/Projects/Ressources/Models/Old chair/container.jpg", Texture::DIFFUSE);

	Skybox skybox;
	skybox.ConfigureSkybox();

	//cube centrale (couleur)
	Cube cube;
	//cube.SetObjectColor(glm::vec3(1.0, 0.51, 0.3));
	 
	// 
	Cube cube2;
	cube2.AddTexture(containerTexture);
	cube2.AddTexture(containerSpecularMap);

	Cube cube3;
	Cube cube4;
	Cube cube5;
	Cube cube6;
	Cube cube7;

	//cube.AddTexture(texture2);
	//cube.SetObjectColor(glm::vec3(1.0f, 0.5f, 0.31f));
	Material cubeMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.3f, 0.3f, 0.3f));
	cube.SetMaterial(cubeMaterial);
	cube2.SetMaterial(cubeMaterial);
	cube3.SetMaterial(cubeMaterial);
	cube4.SetMaterial(cubeMaterial);
	cube5.SetMaterial(cubeMaterial);
	cube6.SetMaterial(cubeMaterial);
	cube7.SetMaterial(cubeMaterial);

	Cube lightMesh;
	lightMesh.SetObjectColor(glm::vec3(0.0f, 0.0f, 0.4f));
	Cube lightMesh2;
	lightMesh2.SetObjectColor(glm::vec3(0.9f, 0.9f, 0.0f));

	Plane plane(10, 10, 5);
	plane.AddTexture(parquet);
	plane.SetMaterial(cubeMaterial);

	Plane wall1(10, 10, 5);
	wall1.AddTexture(brickwallTexture);
	Plane wall2(10, 10, 5);
	wall2.AddTexture(brickwallTexture);
	Plane wall3(10, 10, 5);
	wall3.AddTexture(brickwallTexture);
	Plane wall4(10, 10, 5);
	wall4.AddTexture(brickwallTexture);

	Model nano("C:/Users/Julien/Documents/Visual Studio 2015/Projects/Ressources/Models/nanosuit/nanosuit.obj");
	Model teapot("C:/Users/Julien/Documents/Visual Studio 2015/Projects/Ressources/Models/teapot.obj");
	Model island("C:/Users/Julien/Documents/Visual Studio 2015/Projects/Ressources/Models/Small Tropical Island/Small Tropical Island.obj");
	
	teapot.SetMaterial(cubeMaterial);

	while (!glfwWindowShouldClose(windowManager.GetGLFWwindow()))
	{
		// check and call events
		glfwPollEvents();
		windowManager.KeyboardMovement();

		//rendering commands
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox.Draw();

		cube2.Rotate((GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		cube2.Translate(glm::vec3(2.0f, 0.0f, 2.0f));
	
		cube2.Draw(LightingModel::PHONG_SPECULAR);

		plane.Rotate(90.0f, glm::vec3(1.0, 0.0, 0.0));
		plane.Scale(glm::vec3(15.0, 15.0, 15.0));
		//plane.Draw(LightingModel::PHONG_TEXTURE);

		wall1.Scale(glm::vec3(15.0, 15.0, 15.0));
		//wall1.Draw(LightingModel::PHONG_TEXTURE);

		lightMesh.Translate(glm::vec3(2.0f,3.0f,1.0f));
		lightMesh.Scale(glm::vec3(0.2, 0.2, 0.2));
		lightMesh.Draw(LightingModel::COLOR_ONLY);

		lightMesh2.Translate(glm::vec3(-2.0f,3.0f, -2.0f));
		lightMesh2.Scale(glm::vec3(0.2, 0.2, 0.2));
		lightMesh2.Draw(LightingModel::COLOR_ONLY);

		nano.Rotate((GLfloat)glfwGetTime() * 50, glm::vec3(0.0f, 1.0f, 0.0f));
		nano.Scale(glm::vec3(0.25f, 0.25f, 0.25f));
		nano.Draw(LightingModel::PHONG_SPECULAR);

		teapot.Translate(glm::vec3(-4.0f, 0.0f, -6.0f));
		teapot.Draw(LightingModel::PHONG_COLOR);

		island.Translate(glm::vec3(0.0f, -5.0f, 0.0f));
		island.Scale(glm::vec3(0.1f, 0.1f, 0.1f));
		island.Draw(LightingModel::PHONG_SPECULAR);

		//swap buffers
		glfwSwapBuffers(windowManager.GetGLFWwindow());
	}

	glfwTerminate();

	return 0;
}

