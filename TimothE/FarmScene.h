#pragma once
#include "Scene.h"
#include "PlayerInputComponent.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "Fighter.h"
#include "Health.h"
#include "CropPlot.h"
#include "FarmlandManager.h"

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
	GameObject* _pPlayerObject = nullptr;
	GameObject* _pWeaponObject = nullptr;

	PlayerInputComponent* _pPlayerMovement = nullptr;
	MovementComponent* _pMovement = nullptr;

	AnimatedSpritesheet* _pAnimSheet;

	SpriteComponent* _pSc = nullptr;

	SpriteSheet* _pSpritesheet;

	Health* _pPlayerHealth = nullptr;
	Health* _pEnemyHealth = nullptr;

	//CropPlot* _pCropPlot = nullptr;
	/*vector<GameObject*> _pCropPlotObjects;
	vector<SpriteComponent*> _pCropPlotSpriteComponents;
	SpriteComponent* _pCropPlotBaseSpriteComponent = nullptr;
	GameObject* _pCropPlotBaseObject = nullptr;*/
	FarmlandManager* farmland;


	bool farmKeyPressed = false;
};

