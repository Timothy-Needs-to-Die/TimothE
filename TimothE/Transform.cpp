#include "Transform.h"


Transform::Transform(GameObject* pParent)
	: _transformationMatrix(glm::mat4(1.0f)), _position(glm::vec2(0.0f)), _rotation(0.0f), _size(glm::vec2(32.0f)), Component(pParent)
{
	SetType(Component::Transform_Type);
	SetCategory(Component::Transform_Category);
	CalculateTransformMatrix();

	editorPos = new float[2];
	editorRot = &_rotation;
	editorScale = new float[2];
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
	editorPos[0] = _position.x;
	editorPos[1] = _position.y;

	// create boxes to set the position
	if (ImGui::InputFloat2("Position", editorPos))
	{
		std::cout << "Position Set" << std::endl;
		// set the position on the game object
		SetPosition(editorPos[0], editorPos[1]);
	}
 
	editorRot =  &_rotation;
	if (ImGui::InputFloat("Rotation", editorRot))
	{
		//TODO: GameObject's only rotate on X axis
		SetRotation(*editorRot);
	}

	editorScale[0] = _size.x;
	editorScale[1] = _size.y;
	if (ImGui::InputFloat2("Scale", editorScale))
	{
		SetScale(glm::vec2(editorScale[0], editorScale[1]));
	}
}

void Transform::OnEnd()
{
}
