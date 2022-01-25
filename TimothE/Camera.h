#pragma once

#include "pch.h"
#include "Input.h"

class Camera
{
public:
	Camera(float left, float right, float bottom, float top);

	void Update(float dt);

	glm::mat4 Proj() {
		return _mProjection;
	}

	glm::mat4 View() {
		return _mView;
	}

	glm::mat4 ViewProj() {
		return _viewProj;
	}

	glm::vec3 Position() {
		return _mCameraPos;
	}
	void ProcessScrollMovement(float yOffset);

	void RecalculateViewMatrix();

private:
	void PollInput(float dt);

private:
	glm::vec3 _mCameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	float _rotation;

	glm::mat4 _mProjection;
	glm::mat4 _mView;
	glm::mat4 _viewProj;

};

