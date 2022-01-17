#include "Camera.h"

Camera::Camera(GLFWwindow * window, int width, int height, float fov)
{
	//sets window for camera
	_pWindow = window;
	//camera size
	this->_mFOV = fov;
	this->_mWidth = width;
	this->_mHeight = height;
	//camera perspectives
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(_mCameraPos - cameraTarget);
	glm::vec3 cameraRight = glm::normalize(glm::cross(_mCameraUp, cameraDirection));

	_mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	//sets orthographic view
	_mProjection = glm::ortho(0.0f, (float)width / (float)height, 0.1f, 1000.0f);
}

//updates camera lookat
void Camera::Update(float dt)
{
	//PollInput(dt);

	_mView = glm::lookAt(_mCameraPos, _mCameraPos + _mCameraFront, _mCameraUp);
}

//changes FOV when scrolling
void Camera::ProcessScrollMovement(float yOffset)
{
	_mFOV -= yOffset;
	if (_mFOV < 1.0f) {
		_mFOV = 1.0f;
	}
	if (_mFOV > 45.0f) {
		_mFOV = 45.0f;
	}
	_mProjection = glm::perspective(glm::radians(_mFOV), (float)_mWidth / (float)_mHeight, 0.1f, 100.0f);
}

//polls for movement for control
void Camera::PollInput(float dt)
{
	float cameraSpeed = 12.5f * dt;
	if (glfwGetKey(_pWindow, GLFW_KEY_W) == GLFW_PRESS)
		_mCameraPos += cameraSpeed * _mCameraFront;
	if (glfwGetKey(_pWindow, GLFW_KEY_S) == GLFW_PRESS)
		_mCameraPos -= cameraSpeed * _mCameraFront;
	if (glfwGetKey(_pWindow, GLFW_KEY_A) == GLFW_PRESS)
		_mCameraPos -= glm::normalize(glm::cross(_mCameraFront, _mCameraUp)) * cameraSpeed;
	if (glfwGetKey(_pWindow, GLFW_KEY_D) == GLFW_PRESS)
		_mCameraPos += glm::normalize(glm::cross(_mCameraFront, _mCameraUp)) * cameraSpeed;
}
