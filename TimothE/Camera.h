#pragma once

#include "pch.h"

class Camera
{
public:
	Camera(GLFWwindow* window, int width, int height, float fov);


	void Update(float dt);

	float* Proj() {
		return glm::value_ptr(_mProjection);
	}

	float* View() {
		return glm::value_ptr(_mView);
	}

	float* Position() {
		return glm::value_ptr(_mCameraPos);
	}

	glm::mat4 ProjMat() {
		return _mProjection;
	}

	glm::mat4 ViewMat() {
		return _mView;
	}

	glm::vec3 PositionVec() {
		return _mCameraPos;
	}

	float* Front() {
		return glm::value_ptr(_mCameraFront);
	}

	void ProcessScrollMovement(float yOffset);

	float _mPitch = 0.0f;
	float _mYaw = -90.0f;

	float _mFOV = 45.0f;

private:
	void PollInput(float dt);

private:
	glm::vec3 _mCameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _mCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 _mCameraTarget;
	glm::vec3 _mCameraDirection;


	glm::vec3 _mCameraRight;

	glm::mat4 _mProjection;
	glm::mat4 _mView;

	int _mWidth;
	int _mHeight;

	GLFWwindow* _pWindow;
};

