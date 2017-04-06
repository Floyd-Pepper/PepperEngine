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
#include "Framebuffer.h"
#include "ScreenQuad.h"

#include "Defs.h"

#include <iostream>

int main()
{
	WindowManager windowManager(1920, 1080);
	EngineManager::Instance().InitializeEngine();

	// lights
 	DirectionalLight dirLight(glm::vec3(1.0f,1.0f,1.0f));
	EngineManager::Instance().AddDirectionalLight(dirLight);
	PointLight pointLight(glm::vec3(2.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.1f, 0.1f, 1.0f), glm::vec3(0.1f, 0.1f, 1.0f), 1.0f, 0.045f,  0.0075f);
	EngineManager::Instance().AddPointLight(pointLight);
	PointLight pointLight2(glm::vec3(-2.0f, 3.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.9f, 0.9f, 0.0f), glm::vec3(0.9f, 0.9f, 0.0f));
	EngineManager::Instance().AddPointLight(pointLight2);

	Texture texture1("../Ressources/Textures/container.jpg", Texture::DIFFUSE, Texture::MirroredRepeat, Texture::Nearest);
	Texture containerTexture("../Ressources/Textures/container2.png", Texture::DIFFUSE);
	Texture containerSpecularMap("../Ressources/Textures/container2_specular.png", Texture::SPECULAR);
	Texture parquet("../Ressources/Textures/parquet.png", Texture::DIFFUSE);

	Skybox skybox;
	std::vector<const GLchar*> faces;
	faces.push_back("../Ressources/Textures/Skybox/right.jpg");
	faces.push_back("../Ressources/Textures/Skybox/left.jpg");
	faces.push_back("../Ressources/Textures/Skybox/top.jpg");
	faces.push_back("../Ressources/Textures/Skybox/bottom.jpg");
	faces.push_back("../Ressources/Textures/Skybox/back.jpg");
	faces.push_back("../Ressources/Textures/Skybox/front.jpg");
	skybox.ConfigureSkybox(faces);

	Cube cube;
	cube.AddTexture(containerTexture);
	cube.AddTexture(containerSpecularMap);

	Material cubeMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.3f, 0.3f, 0.3f));
	cube.SetMaterial(cubeMaterial);

	Cube lightMesh;
	lightMesh.SetObjectColor(glm::vec3(0.0f, 0.0f, 0.4f));
	Cube lightMesh2;
	lightMesh2.SetObjectColor(glm::vec3(0.9f, 0.9f, 0.0f));

	Model nano("../Ressources/Models/nanosuit/nanosuit.obj");
	Model teapot("../Ressources/Models/teapot.obj");
	//Model island("../Ressources/Models/Small Tropical Island/Small Tropical Island.obj");
	Model sponza("../Ressources/Models/crytek-sponza/sponza.obj");
	
	teapot.SetMaterial(cubeMaterial);

	Framebuffer framebuffer(1920, 1080);
	framebuffer.Create();

	ScreenQuad screenQuad(framebuffer);

	while (!glfwWindowShouldClose(windowManager.GetGLFWwindow()))
	{
		// check and call events
		glfwPollEvents();
		windowManager.KeyboardMovement();

		framebuffer.Activate();

		// we draw the entire scene with the custom framebuffer bind

		//rendering commands
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		cube.Rotate((GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		cube.Translate(glm::vec3(2.0f, 0.5f, 2.0f));
	
		cube.Draw(LightingModel::BLINN_PHONG);

		lightMesh.Translate(glm::vec3(2.0f,3.0f,1.0f));
		lightMesh.Scale(glm::vec3(0.2, 0.2, 0.2));
		lightMesh.Draw(LightingModel::COLOR_ONLY);

		lightMesh2.Translate(glm::vec3(-2.0f,3.0f, -2.0f));
		lightMesh2.Scale(glm::vec3(0.2, 0.2, 0.2));
		lightMesh2.Draw(LightingModel::COLOR_ONLY);

		nano.Rotate((GLfloat)glfwGetTime() * 50, glm::vec3(0.0f, 1.0f, 0.0f));
		nano.Scale(glm::vec3(0.25f, 0.25f, 0.25f));
		nano.Draw(LightingModel::BLINN_PHONG);

		teapot.Translate(glm::vec3(6.0f, 0.0f, -4.0f));
		teapot.Draw(LightingModel::BLINN_PHONG);

		//island.Translate(glm::vec3(0.0f, -5.0f, 0.0f));
		//island.Scale(glm::vec3(0.1f, 0.1f, 0.1f));
		//island.Draw(LightingModel::BLINN_PHONG);

		sponza.Scale(glm::vec3(0.02f, 0.02f, 0.02f));
		sponza.Draw(LightingModel::BLINN_PHONG);

		skybox.Draw();

		// draw the quad with attached the screen texture of the custom framebuffer
		screenQuad.Draw();

		//swap buffers
		glfwSwapBuffers(windowManager.GetGLFWwindow());
	}

	glfwTerminate();

	return 0;
}

