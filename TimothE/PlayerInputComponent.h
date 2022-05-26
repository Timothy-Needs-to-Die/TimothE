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
#include "FarmlandManager.h"


enum class StructureType {
	Wall,
	Tower,
	Campfire
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
	void FarmingControls();

	void BuildControls();

	void NearbyResourceNode(class ResourceNode* nearbyResource);
	glm::vec2 GetPlayerMidpoint(glm::vec2 target)
	{
		// Targets the midpoint of the player
		target.x += _pParentObject->GetTransform()->GetScale().x / 2;
		target.y += _pParentObject->GetTransform()->GetScale().y / 2;
		return target;
	}

	virtual void OnTriggerEnter(ColliderBase* other) override;
	virtual void OnTriggerExit(ColliderBase* other) override;
private:
	TileMap* _pTileMap;
	MovementComponent* _pMovement = nullptr;
	Fighter* _pFighter = nullptr;

	FarmlandManager* _pFarmlandManager = nullptr;

	class ResourceNode* _pNearbyResourceNode = nullptr;

	StructureType _selectedStructure;

	bool _inBuildMode = false;
	bool _bFarmMode = false;
	bool _bReadyforbuildPress = false;

	// input bools
	bool _bFkeyPressed;
	bool _bGkeyPressed;
	bool _bHkeyPressed;
};

