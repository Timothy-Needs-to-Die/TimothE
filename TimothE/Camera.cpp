#include "pch.h"
#include "Camera.h"
#include "Time.h"

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
	_mName = name;


	_left = left;
	_right = right;
	_top = top;
	_bottom = bottom;

	RecalculateViewMatrix();
}
void Camera::OnStart()
{
}
void Camera::OnEnd()
{
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
	ImGui::InputFloat("X", &x);
	ImGui::InputFloat("Y", &y);
	ImGui::InputFloat("Z", &z);
	ImGui::Text("Rotation"); ImGui::SameLine();
	ImGui::InputFloat("Rotation", &_rotation);
	SetPosition(glm::vec3(x,y,z));
}

void Camera::OnUpdate()
{
	if (_mName == "Editor") {
		PollInput();
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
