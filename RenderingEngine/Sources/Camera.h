#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Camera
{
public:
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

public:
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
	~Camera();
	glm::mat4 GetViewMatrix();
	const glm::vec3& GetPosition() { return _Position; }

	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	void ProcessMouse(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

private:
	void UpdateVectors();

private:
	glm::vec3 _Position;
	glm::vec3 _Target;
	glm::vec3 _Direction;

	glm::vec3 _WorldUp;

	glm::vec3 _Up;
	glm::vec3 _Right;
	glm::vec3 _Front;

	GLfloat _Yaw = -90.0f;
	GLfloat _Pitch = 0.0f;

	GLfloat _MouseSensitivity = 0.15f;

	GLfloat _MovementSpeed = 5.0f;
};