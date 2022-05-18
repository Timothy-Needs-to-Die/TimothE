#pragma once
#include "Scene.h"
#include "PlayerInputComponent.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "Fighter.h"
#include "Health.h"
#include "Wave.h"
#include "ResourceNode.h"

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


	WaveController* _pWaveController = nullptr;

	class Player* _pPlayer;
	
	class ResourceNodeObject* _pWoodNode = nullptr;
};

