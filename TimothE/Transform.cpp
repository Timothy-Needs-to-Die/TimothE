#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"


Transform::Transform(GameObject* pParent)
	: _globalPosition(glm::vec2(0.0f)), _rotation(0.0f), _size(glm::vec2(0.25f)), _localPosition(0.0f), _renderQuad{}, Component(pParent)
{
	//Sets the type and category for the component
	SetType(Component::Transform_Type);

}


void Transform::OnStart()
{
	
}

void Transform::OnUpdate()
{
	GameObject* pParent = _pOwner->GetOwner();
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

	_renderQuad.position = _globalPosition;
}

float Transform::GetRotation() const
{
	if (_pOwner->GetOwner() != nullptr) {
		return _pOwner->GetOwner()->GetTransform()->GetRotation() + _rotation;
	}
	return _rotation;
}

void Transform::OnEnd()
{

}
