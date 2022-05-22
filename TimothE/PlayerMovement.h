#pragma once
#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Input.h"
#include "TileData.h"
#include "TileMap.h"
#include "Physics.h"
#include "MovementComponent.h"


class PlayerMovement : public Component
{
public:
	COMPONENT_STATIC_TYPE(PlayerMovement);

	PlayerMovement(GameObject* parent) : Component(parent) {
		SetType(Types::PlayerMovement);
	}

	void SetTileMap(TileMap* pTileMap) {
		_pTileMap = pTileMap;
	}

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;

private:
	TileMap* _pTileMap;
	MovementComponent* _pMovement;
};

