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
	float* pos = new float[2]{ GetPosition()->_x, GetPosition()->_y };
	// create boxes to set the position
	if (ImGui::InputFloat2("Position", pos))
	{
		// set the position on the game object
		SetPosition(pos[0], pos[1]);
	}

	float* rot = new float[2]{ GetXrotation(), GetYrotation() };
	if (ImGui::InputFloat2("Rotation", rot))
	{
		SetXrotation(rot[0]);
		SetYrotation(rot[1]);
	}

	float* scale = new float[2]{ GetXScale(), GetYScale() };
	if (ImGui::InputFloat2("Scale", scale))
	{
		SetXScale(scale[0]);
		SetYScale(scale[1]);
	}
}

void Transform::SetPosition(float x, float y)
{
}

void Transform::OnEnd()
{
}

void Transform::SetYrotation(float yRot)
{
	_yRot = yRot;
}

void Transform::SetXScale(float scale)
{
	_scaleX = scale;
}

void Transform::SetYScale(float scale)
{
	_scaleY = scale;
}
