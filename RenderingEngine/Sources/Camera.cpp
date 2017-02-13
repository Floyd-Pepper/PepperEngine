#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 position, glm::vec3 up) : _Front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	_Position = position;
	_WorldUp = up;
	UpdateVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(_Position, _Position + _Front, _Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = _MovementSpeed * deltaTime;
	std::string deb = debug;
	if (direction == FORWARD)
		_Position += _Front * velocity;
	if (direction == BACKWARD)
		_Position -= _Front * velocity;
	if (direction == LEFT)
		_Position -= _Right * velocity;
	if (direction == RIGHT)
		_Position += _Right * velocity;
}

void Camera::ProcessMouse(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= _MouseSensitivity;
	yoffset *= _MouseSensitivity;

	_Yaw += xoffset;
	_Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (_Pitch > 89.0f)
			_Pitch = 89.0f;
		if (_Pitch < -89.0f)
			_Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	UpdateVectors();
}

void Camera::UpdateVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
	front.y = sin(glm::radians(_Pitch));
	front.z = sin(glm::radians(_Yaw)) * cos(glm::radians(_Pitch));
	_Front = glm::normalize(front);
	_Right = glm::normalize(glm::cross(_Front, _WorldUp));
	_Up = glm::normalize(glm::cross(_Right, _Front));
}

