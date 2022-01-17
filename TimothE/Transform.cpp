#include "Transform.h"
#include "imgui.h"

Transform::Transform()
{
	_transformationMatrix = glm::mat4(1.0f);
	_position = glm::vec2(640, 360);
	_transformationMatrix = glm::scale(_transformationMatrix, { 1.0f, 1.0f, 1 });
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(_position, 0));
}

void Transform::Translate(glm::vec2 newPos)
{
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(newPos, 0));
}

void Transform::Scale(glm::vec2 newSize)
{
	_transformationMatrix = glm::scale(_transformationMatrix, { newSize, 1 });
}

void Transform::Rotate(float rotationAmount, glm::vec2 axis)
{
	_transformationMatrix = glm::rotate(_transformationMatrix, rotationAmount, { axis, 0 });
}

void Transform::OnStart()
{
}

void Transform::OnUpdate()
{
}

void Transform::EditorUI()
{
	ImGui::Text("Transform");

	// get the position
	float* pos = new float[2]{ GetPosition().x, GetPosition().y };
	// create boxes to set the position
	if (ImGui::InputFloat2("Position", pos))
	{
		// set the position on the game object
		Translate(glm::vec2(pos[0], pos[1]));
	}

	float* rot = new float[2]{ GetRotation() };
	if (ImGui::InputFloat2("Rotation", rot))
	{
		Rotate(0, glm::vec2(rot[0], rot[1]));
	}

	float* scale = new float[2]{ GetScale().x, GetScale().y };
	if (ImGui::InputFloat2("Scale", scale))
	{
		Scale(glm::vec2(scale[0], scale[1]));
	}
}

void Transform::OnEnd()
{
}
