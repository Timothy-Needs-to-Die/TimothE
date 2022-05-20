#include "CircleColliderComponent.h"
#include "Transform.h"
#include "GameObject.h"

CircleColliderComponent::CircleColliderComponent(GameObject* owner)
	: ColliderBase(owner, Circle)
{
	SetType(Component::Collider);
	SetCategory(Component::Collisions_Category);
}

void CircleColliderComponent::OnStart()
{

}

void CircleColliderComponent::OnUpdate()
{
	Transform* pOwnerTransform = _pParentObject->GetTransform();

	_radius = pOwnerTransform->GetScale().x * _scale;
	_position = pOwnerTransform->GetPosition();
}

void CircleColliderComponent::OnEnd()
{

}
