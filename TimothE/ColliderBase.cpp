#include "pch.h"
#include "ColliderBase.h"

void ColliderBase::Triggered()
{
	for (int i = 0; i < _onTriggerCalls.size(); i++) {
		_onTriggerCalls[i]();
	}
}

void ColliderBase::Collided()
{
	for (int i = 0; i < _onCollisionCalls.size(); i++) {
		_onCollisionCalls[i]();
	}
}

void ColliderBase::AddTriggerEvent(void(*function)())
{
	_onTriggerCalls.push_back(function);
}

void ColliderBase::AddCollisionEvent(void(*function)())
{
	_onCollisionCalls.push_back(function);
}

void ColliderBase::RemoveTriggerEvent(void(*function)())
{
	_onTriggerCalls.erase(std::find(_onTriggerCalls.begin(), _onTriggerCalls.end(), function));
}

void ColliderBase::RemoveCollisionEvent(void(*function)())
{
	_onCollisionCalls.erase(std::find(_onCollisionCalls.begin(), _onCollisionCalls.end(), function));
}
