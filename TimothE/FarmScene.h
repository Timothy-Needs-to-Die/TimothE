#pragma once
#include "Scene.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "Fighter.h"
#include "Health.h"
#include "InventoryScreen.h"

#include "ResourceNode.h"
#include "FarmlandManager.h"
#include "PlantResourceType.h"
#include "Button.h"
#include "CameraManager.h"

class FarmScene : public Scene
{
public:

	FarmScene(std::string name) : Scene(name)
	{

	}

	~FarmScene();

	void UpdateUI() override;
	void UpdateObjects() override;
	void InitScene() override;

	void AddStructure(class StructureObject* object);
	void RemoveStructure(class StructureObject* object);
	std::vector<class StructureObject*> GetStructures() const;

	void GameOver() override;

	class GameTimeManager* GetGameTime() { return _pGameTime; }

private:
	GameObject* _pStartButton = nullptr;
	GameObject* _pWeaponObject = nullptr;
	GameObject* _pAITester = nullptr;
	GameObject* _pAITester2 = nullptr;
	GameObject* _pAStar = nullptr;
	InventoryScreen* _pInventoryScreen;

	SpriteSheet* _pSpritesheet;

	//class WaveController* _pWaveController = nullptr;

	class Player* _pPlayer;
	//class OffensiveStructureObject* _pTower = nullptr;
	
	class ResourceNodeObject* _pWoodNode = nullptr;
	class ResourceNodeObject* _pMetalNode = nullptr;
	class ResourceNodeObject* _pStoneNode = nullptr;
	class ResourceNodeObject* _pCoalNode = nullptr;

	class GameTimeManager* _pGameTime = nullptr;

	//Farmland
	FarmlandManager* farmland;
	bool farmKeyPressed = false;
	bool _inventoryKeyPressed = false;

	std::vector<class StructureObject*> _pStructures;

	class Bed* _pBed;
};

