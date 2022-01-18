#include "Transform.h"
#include "imgui.h"

Transform::Transform()
{
	SetType(Component::Transform_Type);
	SetCategory(Component::Transform_Category);
	_transformationMatrix = glm::mat4(1.0f);
	_position = glm::vec2(640, 360);
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(_position, 0));
}

void Transform::Translate(glm::vec2 newPos)
{
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(newPos, 0));
}

void Transform::Scale(glm::vec2 newSize)
{
	_transformationMatrix = glm::scale(_transformationMatrix, { newSize.x / 2, newSize.y / 2, 1 });
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

void Transform::DrawEditorUI()
{
	ImGui::Text("Transform");

	// get the position
	float* pos = new float[2]{ GetPosition().x, GetPosition().y };
	// create boxes to set the position
	if (ImGui::InputFloat2("Position", pos))
	{
		// set the position on the game object
		SetPosition(pos[0], pos[1]);
	}

	float* rot = new float[2]{ GetRotation() };
	if (ImGui::InputFloat2("Rotation", rot))
	{
		//TODO: GameObject's only rotate on X axis
		SetRotation(rot[0]);
	}

	float* scale = new float[2]{ GetScale().x, GetScale().y };
	if (ImGui::InputFloat2("Scale", scale))
	{
		SetScale(glm::vec2(scale[0], scale[1]));
	}
	delete[]pos;
	delete[]rot;
	delete[]scale;
}

void Transform::OnEnd()
{
}
