#include "pch.h"
#include "ColliderBase.h"
#include "Physics.h"


ColliderBase::ColliderBase(GameObject* parent, ColliderType type) : Component(parent), _colType(type)
{
	Physics::AddCollider(this);
	_collidersChannel = CollisionChannel_None;
	_flags = 0;
}

ColliderBase::~ColliderBase()
{
	Physics::RemoveCollider(this);
}
