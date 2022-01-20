#include "Transform.h"
#include "imgui.h"

Transform::Transform()
	: _transformationMatrix(1.0f), _position(glm::vec2(0.1,0.1)), _rotation(0.0f), _size(glm::vec2(300.0f))
{
	SetType(Component::Transform_Type);
	SetCategory(Component::Transform_Category);
	CalculateTransformMatrix();
}

void Transform::Translate(glm::vec2 newPos)
{
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(newPos, 0));
	//_position += newPos;
}

void Transform::Scale(glm::vec2 newSize)
{
	_transformationMatrix = glm::scale(_transformationMatrix, { newSize.x / 2, newSize.y / 2, 1 });
	//_size += newSize;
}

void Transform::Rotate(float rotationAmount, glm::vec2 axis)
{
	_transformationMatrix = glm::rotate(_transformationMatrix, rotationAmount, { axis, 0 });
	//_rotation += rotationAmount;
}

void Transform::OnStart()
{
}

void Transform::OnUpdate()
{
	CalculateTransformMatrix();
}

void Transform::DrawEditorUI()
{
	ImGui::Text("Transform");

	// get the position
	float* pos = new float[2]{ GetPosition().x, GetPosition().y };
	// create boxes to set the position
	if (ImGui::InputFloat2("Position", pos))
	{
		std::cout << "Position Set" << std::endl;
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
