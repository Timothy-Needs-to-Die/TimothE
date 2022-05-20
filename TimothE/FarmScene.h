#pragma once
#include "Scene.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "Fighter.h"
#include "Health.h"

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

protected:


private:
	GameObject* _pStartButton = nullptr;
	GameObject* _pWeaponObject = nullptr;

	SpriteSheet* _pSpritesheet;

	//class WaveController* _pWaveController = nullptr;

	class Player* _pPlayer;
	class OffensiveStructureObject* _pTower = nullptr;

	//Day* _pDay;
	bool _timeProgression = true;
	
	class ResourceNodeObject* _pWoodNode = nullptr;

	//Farmland
	FarmlandManager* farmland;
	bool farmKeyPressed = false;
};

