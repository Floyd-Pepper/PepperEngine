// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#pragma once

class WindowManager {
public:
	WindowManager(int width = 800, int height = 600);
	~WindowManager();

	void InitialiseGLFW();
	void InitialiseGLEW();

	// user inputs
	void KeyboardMovement();
	void SetKeyCallBacks();

	void SetViewPort();

	void SetOptions();

	GLFWwindow* GetGLFWwindow() const { return _GLFWwindow; }

private:
	GLFWwindow* _GLFWwindow;
	int _Width;
	int _Height;

	GLfloat _DeltaTime = 0.0f;
	GLfloat _LastFrame = 0.0f;
};