#include "pch.h"
#include "Camera.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "TileMap.h"

Camera::Camera(float left, float right, float bottom, float top, std::string name, GameObject* parent) : Component(parent)
{
	SetType(Component::Camera_Type);
	std::cout << "Camera created" << std::endl;
	_cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
	_view = glm::mat4(1.0f);
	_projection = glm::ortho(left, right, bottom, top, -2.0f, 2.0f);
	_rotation = 0.0f;
	_aspectRatio = abs(left);
	_zoomLevel = abs(bottom);
	_name = name;


	_left = left;
	_right = right;
	_top = top;
	_bottom = bottom;

	RecalculateViewMatrix();
}

void Camera::DrawEditorUI()
{
	//displays the texture in the editor window
	ImGui::Text("Camera");
	if (ImGui::Checkbox("IsEnabled", _editorIsEnabled))
	{
		std::cout << "IsEnabled = " << *_editorIsEnabled << std::endl;
		SetEnabled(*_editorIsEnabled);
	}
	ImGui::Text("Aspect Ratio"); ImGui::SameLine();
	ImGui::InputFloat("Aspect Ratio", &_aspectRatio);
	ImGui::Text("Zoom"); ImGui::SameLine();
	ImGui::InputFloat("Zoom", &_zoomLevel);
	
	ImGui::Text("Position");

	ImGui::Text("Rotation"); ImGui::SameLine();
	ImGui::InputFloat("Rotation", &_rotation);
}

void Camera::OnUpdate()
{
	if (_name == "Editor") {
		PollInput();
	}

	if (_pFollowTarget != nullptr)
	{
		glm::vec2 followTargetPos = _pFollowTarget->GetTransform()->GetPosition();

		glm::vec3 adjustedPos;
		adjustedPos.x = followTargetPos.x + _followTargetOffset.x;
		adjustedPos.y = followTargetPos.y + _followTargetOffset.y;
		adjustedPos.z = _followTargetOffset.z;

		_cameraPos = adjustedPos;

		if (_pCurrentMap != nullptr) {
			float camXMin = _cameraPos.x + _left; //Left is negative
			float camXMax = _cameraPos.x + _right;
			float camYMin = _cameraPos.y + _bottom; //Bottom is negative
			float camYMax = _cameraPos.y + _top;

			float tilemapXMin = 0.0f;
			float tilemapXMax = _pCurrentMap->GetMapSize().x;
			float tilemapYMin = 0.0f;
			float tilemapYMax = _pCurrentMap->GetMapSize().y;

			if (camXMin < tilemapXMax && camXMax > tilemapXMax) {
				int noOfTiles = _pCurrentMap->GetTileMapDimensions().x;
				_cameraPos.x = 0.25f * (noOfTiles / 2);
			}
			else if (camXMin < tilemapXMin) {
				_cameraPos.x = tilemapXMin - _left;
			}
			else if (camXMax > tilemapXMax) {
				_cameraPos.x = tilemapXMax - _right;
			}

			if (camYMin < tilemapYMin && camYMax + 0.25f> tilemapYMax) {
				int noOfTiles = _pCurrentMap->GetTileMapDimensions().y;
				_cameraPos.y = 0.25f * (noOfTiles / 2);
			}
			else if (camYMin < tilemapYMin) {
				_cameraPos.y = tilemapYMin - _bottom;
			}
			else if (camYMax > tilemapYMax) {
				_cameraPos.y = tilemapYMax - _top;
			}
		}
	}

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
	_projection = glm::ortho(left, right, bottom, top, -2.0f, 2.0f);
}

void Camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), _cameraPos) *
		glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

	_view = glm::inverse(transform);
	_viewProj = _projection * _view;
}

//polls for movement for control
void Camera::PollInput()
{
	if (Input::IsKeyDown(KEY_W) || Input::IsKeyHeld(KEY_W)) {
		float yOffset = (float)cos(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
		float xOffset = (float)-sin(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
		_cameraPos.x += xOffset;
		_cameraPos.y += yOffset;
	}
	if (Input::IsKeyDown(KEY_S) || Input::IsKeyHeld(KEY_S)) {
		_cameraPos.x -= (float)-sin(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
		_cameraPos.y -= (float)cos(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
	}
	if (Input::IsKeyDown(KEY_A) || Input::IsKeyHeld(KEY_A)) {
		_cameraPos.x -= (float)cos(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
		_cameraPos.y -= (float)sin(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
	}
	if (Input::IsKeyDown(KEY_D) || Input::IsKeyHeld(KEY_D)) {
		_cameraPos.x += (float)cos(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
		_cameraPos.y += (float)sin(glm::radians(_rotation)) * _cameraSpeed * Time::GetDeltaTime();
	}
}
