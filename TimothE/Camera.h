#pragma once

#include "pch.h"
#include "Input.h"

class Camera
{
public:
	Camera(float left, float right, float bottom, float top);

	void Update(float dt);

	glm::mat4 Proj() { return _projection; }
	glm::mat4 View() { return _view; }
	glm::mat4 ViewProj() { return _viewProj; }
	glm::vec3 Position() { return _cameraPos; }

	void SetCameraSpeed(float speed) { _cameraSpeed = speed; }
	float GetCameraSpeed() const { return _cameraSpeed; }

	void ProcessScrollMovement(float yOffset);

	void RecalculateViewMatrix();

private:
	void PollInput(float dt);

private:
	glm::vec3 _cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
	float _rotation;

	float _cameraSpeed = 10.0f;

	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProj;

};

