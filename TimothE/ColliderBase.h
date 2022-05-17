#pragma once
#include "pch.h"
#include "Component.h"

enum ColliderType {
	Circle,
	Box
};


class ColliderBase : public Component
{
public:
	ColliderBase(GameObject* parent, ColliderType type) : Component(parent), _type(type) {}

	COMPONENT_STATIC_TYPE(Collider)

	void Triggered(ColliderBase* other);
	void Collided(ColliderBase* other);

	void AddTriggerEvent(void(*function)(ColliderBase*));
	void AddCollisionEvent(void(*function)(ColliderBase*));

	void RemoveTriggerEvent(void(*function)(ColliderBase*));
	void RemoveCollisionEvent(void(*function)(ColliderBase*));

	bool IsTrigger() const { return _isTrigger; }
	void SetTrigger(bool val) { _isTrigger = val; }

	ColliderType GetType() const { return _type; }

protected:
	std::vector<void(*)(ColliderBase*)> _onTriggerCalls;
	std::vector<void(*)(ColliderBase*)> _onCollisionCalls;

	bool _isTrigger;

	ColliderType _type;
};

