#pragma once
#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Input.h"
#include "Physics.h"



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
		target.x += _pOwner->GetTransform()->GetScale().x / 2;
		target.y += _pOwner->GetTransform()->GetScale().y / 2;
		return target;
	}

	virtual void OnTriggerEnter(ColliderBase* other) override;
	virtual void OnTriggerExit(ColliderBase* other) override;
private:
	class TileMap* _pTileMap = nullptr;
	class MovementComponent* _pMovement = nullptr;
	class Fighter* _pFighter = nullptr;

	class FarmlandManager* _pFarmlandManager = nullptr;

	class ResourceNode* _pNearbyResourceNode = nullptr;

	StructureType _selectedStructure = StructureType::Wall;

	bool _inBuildMode = false;
	bool _bFarmMode = false;
};



