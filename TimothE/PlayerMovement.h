#pragma once
#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Input.h"

class PlayerMovement : public Component
{
public:
	COMPONENT_STATIC_TYPE(PlayerMovement);

	PlayerMovement(GameObject* parent) : Component(parent) {
		SetType(Types::PlayerMovement);
	}

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEnd() override;
};

