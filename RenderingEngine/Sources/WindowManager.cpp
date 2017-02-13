#include "WindowManager.h"
#include "EngineManager.h"


WindowManager::WindowManager(int width, int height)
{
	_Width = width;
	_Height = height;
	//initialisation
	try
	{
		InitialiseGLFW();
		InitialiseGLEW();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

WindowManager::~WindowManager()
{

}

void WindowManager::InitialiseGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_GLFWwindow = glfwCreateWindow(_Width, _Height, "Rendering Engine V1", nullptr, nullptr);
	if (_GLFWwindow == nullptr)
	{
		glfwTerminate();
		throw std::exception("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(_GLFWwindow);

	// a deplacer
	SetViewPort();
	SetOptions();

	SetKeyCallBacks();
}

void WindowManager::InitialiseGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Failed to initialize GLEW");
	}
}

static bool _Keys[1024];

void ProcessKeys(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			_Keys[key] = true;
		else if (action == GLFW_RELEASE)
			_Keys[key] = false;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	ProcessKeys(window, key, scancode, action, mode);
}

void WindowManager::KeyboardMovement()
{
	GLfloat currentFrame = glfwGetTime();
	_DeltaTime = currentFrame - _LastFrame;
	_LastFrame = currentFrame;
	auto& engine = EngineManager::Instance();
	Camera& camera = engine.GetCamera();
	// Camera controls
	if (_Keys[GLFW_KEY_W])
		camera.ProcessKeyboard(Camera::Camera_Movement::FORWARD, _DeltaTime);
	if (_Keys[GLFW_KEY_S])
		camera.ProcessKeyboard(Camera::Camera_Movement::BACKWARD, _DeltaTime);
	if (_Keys[GLFW_KEY_A])
		camera.ProcessKeyboard(Camera::Camera_Movement::LEFT, _DeltaTime);
	if (_Keys[GLFW_KEY_D])
		camera.ProcessKeyboard(Camera::Camera_Movement::RIGHT, _DeltaTime);
}

static bool _FirstMouse = true;
static GLfloat _LastXMouse;
static GLfloat _LastYMouse;

void MouseMovement(GLFWwindow* window, double xpos, double ypos)
{
	if (_FirstMouse)
	{
		_LastXMouse = xpos;
		_LastYMouse = ypos;
		_FirstMouse = false;
	}

	GLfloat xoffset = xpos - _LastXMouse;
	GLfloat yoffset = _LastYMouse - ypos;

	_LastXMouse = xpos;
	_LastYMouse = ypos;

	auto& engine = EngineManager::Instance();
	Camera& camera = engine.GetCamera();
	camera.ProcessMouse(xoffset, yoffset);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	MouseMovement(window, xpos, ypos);
}

void WindowManager::SetKeyCallBacks()
{
	glfwSetKeyCallback(_GLFWwindow, key_callback);
	glfwSetCursorPosCallback(_GLFWwindow, mouse_callback);
	glfwSetInputMode(_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowManager::SetViewPort()
{
	glfwGetFramebufferSize(_GLFWwindow, &_Width, &_Height);
	glViewport(0, 0, _Width, _Height);
}

void WindowManager::SetOptions()
{
	glEnable(GL_DEPTH_TEST);
}
