#include "pch.h"
#include "ColliderBase.h"
#include "Physics.h"


ColliderBase::ColliderBase(GameObject* parent, ColliderType type) : Component(parent), _colType(type)
{
	//Adds this as a collider to the physics system
	Physics::AddCollider(this);

	//Default to no channel
	_collidersChannel = CollisionChannel_None;

	//Defaults to compatible with no channels.
	_compatibleChannels = 0;
}

ColliderBase::~ColliderBase()
{
	//Removes this as a collider from the physics system
	Physics::RemoveCollider(this);
}
