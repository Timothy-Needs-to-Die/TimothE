#pragma once
#include "Scene.h"
#include "PlayerInputComponent.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "Fighter.h"
#include "Health.h"
#include "CropPlot.h"

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

	PlayerInputComponent* _pPlayerMovement = nullptr;
	MovementComponent* _pMovement = nullptr;

	AnimatedSpritesheet* _pAnimSheet;

	SpriteComponent* _pSc = nullptr;

	SpriteSheet* _pSpritesheet;

	Health* _pPlayerHealth = nullptr;
	Health* _pEnemyHealth = nullptr;

	//CropPlot* _pCropPlot = nullptr;
	vector<GameObject*> _pCropPlotObjects;
	GameObject* _pCropPlotBaseObject;

	bool farmKeyPressed = false;
};

