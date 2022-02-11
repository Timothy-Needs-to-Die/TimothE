#pragma once

#include "pch.h"
#include "Input.h"
#include "Component.h"

class Camera : public Component
{
public:
	Camera(float left, float right, float bottom, float top, std::string name, GameObject* parent);
	COMPONENT_STATIC_TYPE(Camera_Type);
	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnEnd() override;

	glm::mat4 Proj() { return _projection; }
	glm::mat4 View() { return _view; }
	glm::mat4 ViewProj() { return _viewProj; }
	glm::vec3 Position() { return _cameraPos; }

	void SetPosition(glm::vec3 pos) { _cameraPos = pos; }
	void SetCameraSpeed(float speed) { _cameraSpeed = speed; }
	float GetCameraSpeed() const { return _cameraSpeed; }
	float GetAspectRatio() const { return _aspectRatio; }
	float GetZoomLevel() const { return _zoomLevel; }

	void OnResize(float width, float height);
	void OnMouseScrolled(float yOffset);
	void SetProjection(float left, float right, float bottom, float top);

	void RecalculateViewMatrix();

	glm::vec2 PositionXY() const { return { _cameraPos.x, _cameraPos.y }; }
	glm::vec2 Size() const { return { _aspectRatio, _zoomLevel }; }

	void PrintInfo() {
		std::cout << "Camera: " << _cameraPos.x << ", " << _cameraPos.y << ", " << _cameraPos.z << std::endl;
	}
	std::string _mName;
private:
	void PollInput(float dt);

private:
	glm::vec3 _cameraPos;
	float _rotation;

	float _cameraSpeed = 10.0f;
	float _aspectRatio;
	float _zoomLevel;

	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProj;

	

};

