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

	void SetPosition(glm::vec3 pos) { _cameraPos = pos; }
	void SetCameraSpeed(float speed) { _cameraSpeed = speed; }
	float GetCameraSpeed() const { return _cameraSpeed; }

	void ProcessScrollMovement(float yOffset);

	void RecalculateViewMatrix();

	void PrintInfo() {
		std::cout << "Camera: " << _cameraPos.x << ", " << _cameraPos.y << ", " << _cameraPos.z << std::endl;
	}

private:
	void PollInput(float dt);

private:
	glm::vec3 _cameraPos;
	float _rotation;

	float _cameraSpeed = 10.0f;

	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProj;

};

