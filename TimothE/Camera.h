#pragma once

#include "pch.h"
#include "Input.h"
#include "Component.h"

class Camera : public Component
{
public:
	COMPONENT_STATIC_TYPE(Camera_Type);

	Camera(float left, float right, float bottom, float top, float aspectRatio, std::string name);

	void OnUpdate() override;
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

		_left = -_aspectRatio * _zoomLevel;
		_right = _aspectRatio * _zoomLevel;

		SetProjection(_left, _right, _bottom, _top);
		RecalculateViewMatrix();
	}

	void SetFollowTarget(GameObject* pTarget) {
		_pFollowTarget = pTarget;
	}
	GameObject* GetFollowTarget() const { return _pFollowTarget; }

	void SetTileMap(class TileMap* pMap);

	class TileMap* GetTilemap() const;

	float GetCameraSpeed() const { return _cameraSpeed; }
	float GetAspectRatio() const { return _aspectRatio; }
	float GetZoomLevel() const { return _zoomLevel; }

	void OnResize(float width, float height);
	void OnMouseScrolled(float yOffset);
	void SetProjection(float left, float right, float bottom, float top);

	void SetFollowTargetOffset(glm::vec3 offset) {
		_followTargetOffset = offset;
	}

	void RecalculateViewMatrix();

	glm::vec2 PositionXY() const { return { _cameraPos.x, _cameraPos.y }; }
	glm::vec2 Size() const { return { _aspectRatio, _zoomLevel }; }

	std::string GetName() const { return _name; }

private:
	void PollInput();

private:
	std::string _name;

	glm::vec3 _cameraPos;
	float _rotation;

	float _cameraSpeed = 10.0f;
	float _aspectRatio;
	float _zoomLevel;

	glm::mat4 _projection;
	glm::mat4 _view;
	glm::mat4 _viewProj;

	GameObject* _pFollowTarget = nullptr;
	glm::vec3 _followTargetOffset = glm::vec3{ 0.0f,0.0f,1.0f };

	float _left, _right, _top, _bottom;

	class TileMap* _pCurrentMap = nullptr;
};

