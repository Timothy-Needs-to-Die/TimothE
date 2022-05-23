#pragma once
#include "Scene.h"
#include "PlayerMovement.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "LightLevelManager.h"

class FarmScene : public Scene
{
public:

	FarmScene(std::string name) : Scene(name)
	{

	}

	void UpdateUI() override;
	void UpdateObjects() override;
	void InitScene() override;

	void AddStructure(class StructureObject* object);

protected:


private:
	GameObject* _pStartButton = nullptr;
	GameObject* _pPlayerObject = nullptr;

	PlayerMovement* _pPlayerMovement = nullptr;
	MovementComponent* _pMovement = nullptr;

	AnimatedSpritesheet* _pAnimSheet;

	class Player* _pPlayer;

	LightLevelManager* _pLightManager;

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

	std::vector<class StructureObject*> _pStructures;
};

