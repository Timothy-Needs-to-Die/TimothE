#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top, std::string name, GameObject* parent) : Component(parent)
{
	SetType(Component::Camera_Type);
	SetCategory(Component::Graphics_Category);
	std::cout << "Camera created" << std::endl;
	_cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
	_view = glm::mat4(1.0f);
	_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	_rotation = 0.0f;
	_aspectRatio = abs(left);
	_zoomLevel = abs(bottom);
	_mName = name;
	RecalculateViewMatrix();
}
void Camera::OnStart()
{
}
void Camera::OnEnd()
{
}
void Camera::OnUpdate(float dt)
{
	PollInput(dt);
	RecalculateViewMatrix();
}

void Camera::OnResize(float width, float height)
{
	_aspectRatio = width / height;
	SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
}

void Camera::OnMouseScrolled(float yOffset)
{
	_zoomLevel -= yOffset * 0.25f;
	_zoomLevel = std::max(_zoomLevel, 0.25f); //Max Zoom In
	_zoomLevel = std::min(_zoomLevel, 5.0f); //Max Zoom Out (higher values than 5.0 can cause lag when rendering tile maps)
	SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
}

void Camera::SetProjection(float left, float right, float bottom, float top)
{
	_projection = glm::ortho(left, right, bottom, top);
	_viewProj = _projection * _view;
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
		float yOffset = cos(glm::radians(_rotation)) * _cameraSpeed * dt;
		float xOffset = -sin(glm::radians(_rotation)) * _cameraSpeed * dt;
		_cameraPos.x += xOffset;
		_cameraPos.y += yOffset;
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
