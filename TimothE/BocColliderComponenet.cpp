#include "BoxColliderComponent.h"
#include "GameObject.h"

BoxColliderComponent::BoxColliderComponent() : _size({ 32, 32 }), _isTrigger(false)
{
	_centre = this->gameobject->GetTransform()->GetPosition();
	bounds = new Rect((_centre.x - (_size.x / 2)), (_centre.x - (_size.y / 2)), 
		(_centre.y + (_size.x / 2)), (_centre.y + (_size.y / 2)));
	std::cout << "BoxCollider Component has been added";
}

BoxColliderComponent::~BoxColliderComponent()
{

}

void BoxColliderComponent::OnStart()
{

}

void BoxColliderComponent::OnUpdate()
{

}

void BoxColliderComponent::OnEnd()
{

}

void BoxColliderComponent::DrawEditorUI()
{

}