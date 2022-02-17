#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* parent) : ColliderBase(parent), _radius(NULL), _centre(NULL)
{
	SetType(Component::Boxcollision_Type);
	SetCategory(Component::Collisions_Category);

	_centre = GetParent()->GetTransform()->GetPosition();
	_radius = parent->GetTransform()->GetScale().x / 2;
}

CircleCollider::~CircleCollider()
{

}

void CircleCollider::OnStart()
{

}

void CircleCollider::OnUpdate(float deltaTime)
{
	_centre = _pParentObject->GetTransform()->GetPosition();
	_radius = _pParentObject->GetTransform()->GetScale().x / 2;
}

void CircleCollider::OnEnd()
{

}

void CircleCollider::DrawEditorUI()
{

}
