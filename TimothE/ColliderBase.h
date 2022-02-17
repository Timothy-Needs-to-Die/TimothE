#pragma once
#include "pch.h"
#include "Component.h"

class ColliderBase : public Component
{
public:
	ColliderBase(GameObject* parent) : Component(parent) {}

	void Triggered();
	void Collided();

	void AddTriggerEvent(void(*function)());
	void AddCollisionEvent(void(*function)());

	void RemoveTriggerEvent(void(*function)());
	void RemoveCollisionEvent(void(*function)());

	bool IsTrigger() const { return _isTrigger; }
	void SetTrigger(bool val) { _isTrigger = val; }

protected:
	std::vector<void(*)()> _onTriggerCalls;
	std::vector<void(*)()> _onCollisionCalls;

	bool _isTrigger;
};

