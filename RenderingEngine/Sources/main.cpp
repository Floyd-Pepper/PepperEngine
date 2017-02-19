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

#include "Defs.h"

#include <iostream>

int main()
{
	WindowManager windowManager(1024, 712);
	EngineManager::Instance().InitializeEngine();
	
	/*Shader standardShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\VertexShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\FragmentShader.fs");
	Shader textureShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\TextureShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\TextureShader.fs");
	Shader colorShader("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\ColorShader.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\ColorShader.fs");
	Shader textureNoLighting("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\TextureNoLighting.vs", "C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\RenderingEngine\\RenderingEngine\\Sources\\Shaders\\TextureNoLighting.fs");*/
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

 	DirectionalLight dirLight(glm::vec3(1.0f, 1.0f, 1.0f));
	//EngineManager::Instance().AddDirectionalLight(dirLight);
	PointLight pointLight(glm::vec3(1.0f, 2.0f, 5.0f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	EngineManager::Instance().AddPointLight(pointLight);
	PointLight pointLight2(glm::vec3(-1.0f, 1.0f, -5.0f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	EngineManager::Instance().AddPointLight(pointLight2);

	Texture texture1("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\container.jpg", Texture::MirroredRepeat, Texture::Nearest);
	Texture texture2("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\awesomeface.png", Texture::MirroredRepeat, Texture::Nearest);
	Texture texture3("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\awesomeface.png");
	Texture containerTexture("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\container2.png");
	Texture containerSpecularMap("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\container2_specular.png");
	Texture parquet("C:\\Users\\Julien\\Documents\\Visual Studio 2015\\Projects\\Ressources\\Textures\\parquet.png");
	/*Mesh mesh(vertices, indices);
	mesh.AddTexture(texture1);
	mesh.AddTexture(texture2);

	Mesh mesh2(vertices, indices);
	mesh2.AddTexture(texture1);
	mesh2.AddTexture(texture2);*/

	//cube centrale (couleur)
	Cube cube;
	//cube.SetObjectColor(glm::vec3(1.0, 0.51, 0.3));
	 
	// 
	Cube cube2;
	cube2.AddTexture(containerTexture);
	//cube2.SetSpecularMap(containerSpecularMap);

	Cube cube3;
	Cube cube4;
	Cube cube5;
	Cube cube6;
	Cube cube7;

	//cube.AddTexture(texture2);
	//cube.SetObjectColor(glm::vec3(1.0f, 0.5f, 0.31f));
	Material cubeMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.1f, 0.1f, 0.1f));
	cube.SetMaterial(cubeMaterial);
	cube3.SetMaterial(cubeMaterial);
	cube4.SetMaterial(cubeMaterial);
	cube5.SetMaterial(cubeMaterial);
	cube6.SetMaterial(cubeMaterial);
	cube7.SetMaterial(cubeMaterial);

	Cube lightMesh;
	lightMesh.SetObjectColor(glm::vec3(1.0, 1.0, 1.0));
	Cube lightMesh2;
	lightMesh.SetObjectColor(glm::vec3(1.0, 1.0, 1.0));

	Plane plane;
	plane.AddTexture(parquet);
	plane.SetMaterial(cubeMaterial);
	//plane.SetObjectColor(glm::vec3(1.0f, 0.5f, 0.31f));

	/*std::vector<Cube> cubes;
	for (int i = 0; i < 10; ++i)
		cubes.push_back(Cube());*/
	/*for (const auto& cube : cubes)
	{
		cube.SetShader(shader);
		cube.AddTexture(texture1);
		cube.AddTexture(texture2);
	}
	*/
	while (!glfwWindowShouldClose(windowManager.GetGLFWwindow()))
	{
		// check and call events
		glfwPollEvents();
		windowManager.KeyboardMovement();

		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//EngineManager::Instance().SetLightUniformValues();
		/*mesh.Translate(glm::vec3(0.0f, 1.5f, 0.0f));
		mesh.Rotate((GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f,0.0f,1.0f));
		GLfloat scaleAmount = sin(glfwGetTime());
		mesh.Scale(glm::vec3(scaleAmount, scaleAmount, scaleAmount));*/
		
		//mesh.Draw();

		/*for (GLuint i = 0; i < 10; i++)
		{
			cubes[i].Translate(cubePositions[i]);
			GLfloat angle = 20.0f * i;
			cubes[i].Rotate(angle,glm::vec3(1.0f, 0.3f, 0.5f));
			//cubes[i].Draw();
		}*/
		cube.Rotate((GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		cube.Draw(LightingModel::PHONG_COLOR);

		cube2.Rotate((GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		cube2.Translate(glm::vec3(2.0f, 0.0f, 2.0f));
		cube2.Draw(LightingModel::PHONG_TEXTURE);

		cube3.Rotate((GLfloat)glfwGetTime() * 50, glm::vec3(0.0f, 1.0f, 0.0f));
		cube3.Translate(glm::vec3(-2.0f, 0.0f, -2.0f));
		cube3.Draw(LightingModel::PHONG_COLOR);

		cube4.Rotate((GLfloat)glfwGetTime() * 50, glm::vec3(0.0f, 1.0f, 0.0f));
		cube4.Translate(glm::vec3(-4.0f, 0.0f, -2.0f));
		cube4.Draw(LightingModel::PHONG_COLOR);

		cube5.Rotate((GLfloat)glfwGetTime() * 50, glm::vec3(0.0f, 1.0f, 0.0f));
		cube5.Translate(glm::vec3(-6.0f, 0.0f, -2.0f));
		cube5.Draw(LightingModel::PHONG_COLOR);

		cube6.Rotate((GLfloat)glfwGetTime() * 50, glm::vec3(0.0f, 1.0f, 0.0f));
		cube6.Translate(glm::vec3(-8.0f, 0.0f, -2.0f));
		cube6.Draw(LightingModel::PHONG_COLOR);

		cube7.Rotate((GLfloat)glfwGetTime() * 50, glm::vec3(0.0f, 1.0f, 0.0f));
		cube7.Translate(glm::vec3(-8.0f, 0.0f, -2.0f));
		cube7.Draw(LightingModel::PHONG_COLOR);

		plane.Translate(glm::vec3(0.0, -0.5, 0.0));
		plane.Rotate(90.0f, glm::vec3(1.0, 0.0, 0.0));
		plane.Scale(glm::vec3(15.0, 15.0, 0.0));
		plane.Draw(LightingModel::PHONG_TEXTURE);
		lightMesh.Translate(glm::vec3(1.0f,2.0f,5.0f));
		lightMesh.Scale(glm::vec3(0.2, 0.2, 0.2));
		lightMesh.Draw(LightingModel::COLOR_ONLY);

		lightMesh2.Translate(glm::vec3(-1.0f, 1.0f, -5.0f));
		lightMesh2.Scale(glm::vec3(0.2, 0.2, 0.2));
		lightMesh2.Draw(LightingModel::COLOR_ONLY);
		

		//swap buffers
		glfwSwapBuffers(windowManager.GetGLFWwindow());
	}

	glfwTerminate();

	return 0;
}

