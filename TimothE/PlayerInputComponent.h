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
#include "Fighter.h"


enum class StructureType {
	Wall,
	Tower
};

class PlayerInputComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(PlayerInput);

	PlayerInputComponent(GameObject* parent) : Component(parent) {
		SetType(Types::PlayerInput);
	}

	void SetTileMap(TileMap* pTileMap) {
		_pTileMap = pTileMap;
	}

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;

	void MoveControls();
	void BuildControls();

	void NearbyResourceNode(class ResourceNode* nearbyResource);

	virtual void OnTriggerEnter(ColliderBase* other) override;
	virtual void OnTriggerExit(ColliderBase* other) override;
private:
	TileMap* _pTileMap;
	MovementComponent* _pMovement = nullptr;
	Fighter* _pFighter = nullptr;

	class ResourceNode* _pNearbyResourceNode = nullptr;

	StructureType _selectedStructure;

	bool _inBuildMode = false;
	bool _bReadyforbuildPress = false;
};

