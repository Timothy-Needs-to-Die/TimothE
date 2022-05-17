#include "ColliderBase.h"

void ColliderBase::Triggered(ColliderBase* other)
{
	for (int i = 0; i < _onTriggerCalls.size(); i++) {
		_onTriggerCalls[i](other);
	}
}

void ColliderBase::Collided(ColliderBase* other)
{
	for (int i = 0; i < _onCollisionCalls.size(); i++) {
		_onCollisionCalls[i](other);
	}
}

void ColliderBase::AddTriggerEvent(void(*function)(ColliderBase*))
{
	_onTriggerCalls.push_back(function);
}

void ColliderBase::AddCollisionEvent(void(*function)(ColliderBase*))
{
	_onCollisionCalls.push_back(function);
}

void ColliderBase::RemoveTriggerEvent(void(*function)(ColliderBase*))
{
	_onTriggerCalls.erase(std::find(_onTriggerCalls.begin(), _onTriggerCalls.end(), function));
}

void ColliderBase::RemoveCollisionEvent(void(*function)(ColliderBase*))
{
	_onCollisionCalls.erase(std::find(_onCollisionCalls.begin(), _onCollisionCalls.end(), function));
}
