#include "Transform.h"
#include "imgui.h"

Transform::Transform() 
{
	_position = { 0,0 };
	_size = { 1, 1 };
	_rotation = 0;
	_transformationMatrix = glm::mat4(1.0f);
	_transformationMatrix = glm::scale(_transformationMatrix, { _size, 0 });

}

Transform::Transform(glm::vec2 position, glm::vec2 size, float rotation) : _position(position), _size(size), _rotation(rotation)
{
	_transformationMatrix = glm::mat4(1.0f);
	_transformationMatrix = glm::scale(_transformationMatrix, glm::vec3(_size, 0 ));
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(position, 0));
}

void Transform::Translate(glm::vec2 newPos)
{
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(newPos.x, newPos.y, 0));
}

void Transform::Scale(glm::vec2 newSize)
{
	_transformationMatrix = glm::scale(_transformationMatrix, { newSize, 0 });
}

void Transform::Rotate(float rotationAmount, glm::vec3 axis)
{
	_transformationMatrix = glm::rotate(_transformationMatrix, rotationAmount, axis);
}

void Transform::OnStart()
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
		SetPosition(glm::vec2(pos[0], pos[1]));
	}

	float* rot = new float[1]{ GetRotation() };
	if (ImGui::InputFloat2("Rotation", rot))
	{
		SetRotation(rot[0]);
	}

	float* scale = new float[2]{ GetScale().x, GetScale().y };
	if (ImGui::InputFloat2("Scale", scale))
	{
		SetScale(glm::vec2(scale[0], scale[1]));
	}
}

void Transform::OnEnd()
{
}
