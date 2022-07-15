#include "pch.h"
#include "ColliderBase.h"
#include "Physics.h"


ColliderBase::ColliderBase(GameObject* parent, ColliderType type) : Component(parent), _colType(type)
{
	Physics::AddCollider(this);
}

ColliderBase::~ColliderBase()
{
	Physics::RemoveCollider(this);
}
