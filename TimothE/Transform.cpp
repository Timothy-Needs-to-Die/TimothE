#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"


Transform::Transform(GameObject* pParent)
	: _transformationMatrix(glm::mat4(1.0f)), _globalPosition(glm::vec2(0.0f)), _rotation(0.0f), _size(glm::vec2(0.25f)), _localPosition(0.0f), Component(pParent)
{
	//Sets the type and category for the component
	SetType(Component::Transform_Type);

	//Calculates the transform matrix based on the pos, rot, and scale
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
	//Calculates the transform matrix
	CalculateTransformMatrix();

	GameObject* pParent = _pParentObject->GetParent();
	if (pParent != nullptr) {
		Transform* pTransform = pParent->GetTransform();
		
		try {
			if (pTransform != nullptr)
				_globalPosition = pTransform->GetPosition() + _localPosition;
		}
		catch (std::exception e) {

		}
	}
	else {
		_globalPosition = _localPosition;
	}
}

void Transform::DrawEditorUI()
{
	ImGui::Text("Transform");

	// get the position into the editorPos float array
	editorPos[0] = _globalPosition.x;
	editorPos[1] = _globalPosition.y;

	//Gets the rotation into the editorRotation float*
	editorRot =  &_rotation;

	//Gets the scale into the editorScale float array
	editorScale[0] = _size.x;
	editorScale[1] = _size.y;

	// create boxes to set the position
	if (ImGui::InputFloat2("Position", editorPos))
	{
		// set the position on the game object
		SetPosition(editorPos[0], editorPos[1]);
	}
 
	if (ImGui::InputFloat("Rotation", editorRot))
	{
		SetRotation(*editorRot);
	}

	if (ImGui::InputFloat2("Scale", editorScale))
	{
		SetScale(glm::vec2(editorScale[0], editorScale[1]));
	}
}

float Transform::GetRotation() const
{
	if (_pParentObject->GetParent() != nullptr) {
		return _pParentObject->GetParent()->GetTransform()->GetRotation() + _rotation;
	}
	return _rotation;
}

void Transform::CalculateTransformMatrix() 
{
	//Reset matrix to identity
	_transformationMatrix = glm::mat4(1.0);
	//translate by the position
	_transformationMatrix = glm::translate(_transformationMatrix, glm::vec3(_globalPosition, 0.0f));
	//rotate by the rotation
	_transformationMatrix = glm::rotate(_transformationMatrix, glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	//scale by the scale
	_transformationMatrix = glm::scale(_transformationMatrix, glm::vec3(_size, 1.0f));



}

void Transform::OnEnd()
{

}
