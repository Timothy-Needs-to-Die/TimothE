
#include "Camera.h"

Camera::Camera(GLFWwindow * window, int width, int height, float fov)
{
	_pWindow = window;

	this->fov = fov;
	this->width = width;
	this->height = height;

	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 1000.0f);
}

void Camera::Update(float dt)
{
	PollInput(dt);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{

}

void Camera::ProcessScrollMovement(float yOffset)
{
	fov -= yOffset;
	if (fov < 1.0f) {
		fov = 1.0f;
	}
	if (fov > 45.0f) {
		fov = 45.0f;
	}
	proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
}

void Camera::PollInput(float dt)
{
	float cameraSpeed = 12.5f * dt;
	if (glfwGetKey(_pWindow, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(_pWindow, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(_pWindow, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(_pWindow, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
