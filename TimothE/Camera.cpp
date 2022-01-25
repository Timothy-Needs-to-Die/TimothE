#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top)
{
	_view = glm::mat4(1.0f);
	_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	_rotation = 0.0f;
}

//updates camera lookat
void Camera::Update(float dt)
{
	PollInput(dt);
	RecalculateViewMatrix();
}

//changes FOV when scrolling
void Camera::ProcessScrollMovement(float yOffset)
{
	//_mFOV -= yOffset;
	//if (_mFOV < 1.0f) {
	//	_mFOV = 1.0f;
	//}
	//if (_mFOV > 45.0f) {
	//	_mFOV = 45.0f;
	//}
	//TODO: Reimplemenet
	//_mProjection = glm::ortho(0.0f, (float)_mWidth / (float)_mHeight, 0.1f, 100.0f);
}

void Camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), _cameraPos) *
		glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

	_view = glm::inverse(transform);
	_viewProj = _projection * _view;
}

//polls for movement for control
void Camera::PollInput(float dt)
{
	if (Input::IsKeyDown(KEY_W)) {
		_cameraPos.x += -sin(glm::radians(_rotation)) * _cameraSpeed * dt;
		_cameraPos.y += cos(glm::radians(_rotation)) * _cameraSpeed * dt;
	}
	if (Input::IsKeyDown(KEY_S)) {
		_cameraPos.x -= -sin(glm::radians(_rotation)) * _cameraSpeed * dt;
		_cameraPos.y -= cos(glm::radians(_rotation)) * _cameraSpeed * dt;
	}
	if (Input::IsKeyDown(KEY_A)) {
		_cameraPos.x -= cos(glm::radians(_rotation)) * _cameraSpeed * dt;
		_cameraPos.y -= sin(glm::radians(_rotation)) * _cameraSpeed * dt;
	}
	if (Input::IsKeyDown(KEY_D)) {
		_cameraPos.x += cos(glm::radians(_rotation)) * _cameraSpeed * dt;
		_cameraPos.y += sin(glm::radians(_rotation)) * _cameraSpeed * dt;
	}
}
