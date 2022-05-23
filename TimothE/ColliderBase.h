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
	ColliderBase(GameObject* parent, ColliderType type);
	~ColliderBase();

	COMPONENT_STATIC_TYPE(Collider)

	bool IsTrigger() const { return _isTrigger; }
	void SetTrigger(bool val) { _isTrigger = val; }

	ColliderType GetType() const { return _type; }

	float GetScale() const { return _scale; }
	void SetScale(float val) { _scale = val; }

protected:
	bool _isTrigger;
	float _scale = 1.0f;

	ColliderType _type;
};

