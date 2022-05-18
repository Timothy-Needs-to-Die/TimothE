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

	bool IsTrigger() const { return _isTrigger; }
	void SetTrigger(bool val) { _isTrigger = val; }

	ColliderType GetType() const { return _type; }

protected:
	bool _isTrigger;

	ColliderType _type;
};

