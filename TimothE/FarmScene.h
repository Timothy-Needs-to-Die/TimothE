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

protected:


private:
	GameObject* _pStartButton = nullptr;
	GameObject* _pWeaponObject = nullptr;
	GameObject* _pAITester = nullptr;
	InventoryScreen* _pInventoryScreen;

	SpriteSheet* _pSpritesheet;

	//class WaveController* _pWaveController = nullptr;

	class Player* _pPlayer;
	//class OffensiveStructureObject* _pTower = nullptr;

	//Day* _pDay;
	bool _timeProgression = true;
	
	class ResourceNodeObject* _pWoodNode = nullptr;
	class ResourceNodeObject* _pMetalNode = nullptr;
	class ResourceNodeObject* _pStoneNode = nullptr;
	class ResourceNodeObject* _pCoalNode = nullptr;

	//Farmland
	FarmlandManager* farmland;
	bool farmKeyPressed = false;
	bool _inventoryKeyPressed = false;

	std::vector<class StructureObject*> _pStructures;
};

