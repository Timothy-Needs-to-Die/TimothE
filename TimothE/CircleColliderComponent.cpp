#include "pch.h"
#include "CircleColliderComponent.h"
#include "Transform.h"
#include "GameObject.h"

CircleColliderComponent::CircleColliderComponent(GameObject* owner)
	: ColliderBase(owner, ColliderType::Circle), _position(glm::vec2(0.0f)), _radius(1.0f)
{
	SetType(Component::Collider);
}

void CircleColliderComponent::OnStart()
{

}

void CircleColliderComponent::OnUpdate()
{
	Transform* pOwnerTransform = _pOwner->GetTransform();

	_radius = pOwnerTransform->GetScale().x * _scale;
	_position = pOwnerTransform->GetPosition();
}

void CircleColliderComponent::OnEnd()
{

}
