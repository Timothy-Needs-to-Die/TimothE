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
	void OnUpdate() override;
	void OnEnd() override;
	void DrawEditorUI() override;

	glm::mat4 Proj() { return _projection; }
	glm::mat4 View() { return _view; }
	glm::mat4 ViewProj() { return _viewProj; }
	glm::vec3 Position() { return _cameraPos; }

	void SetPosition(glm::vec3 pos) { _cameraPos = pos; }
	void SetCameraSpeed(float speed) { _cameraSpeed = speed; }
	void SetZoomLevel(float val) {
		_zoomLevel = val;

		_bottom = -_zoomLevel;
		_top = _zoomLevel;

		SetProjection(_left, _right, _bottom, _top);
		RecalculateViewMatrix();
	}

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
	void PollInput();

private:
	glm::vec3 _cameraPos;
	float _rotation;

	float _cameraSpeed = 10.0f;
	float _aspectRatio;
	float _zoomLevel;

	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProj;
	float x, y, z = 0;

	float _left, _right, _top, _bottom;

	

};

