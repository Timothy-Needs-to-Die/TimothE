#pragma once
#include "Scene.h"
#include "PlayerMovement.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"

class FarmScene : public Scene
{
public:

	FarmScene(std::string name) : Scene(name)
	{

	}

	void UpdateUI() override;
	void UpdateObjects() override;
	void InitScene() override;

protected:


private:
	GameObject* _pStartButton = nullptr;
	GameObject* _pPlayerObject = nullptr;

	PlayerMovement* _pPlayerMovement = nullptr;
	MovementComponent* _pMovement = nullptr;

	AnimatedSpritesheet* _pAnimSheet;

	SpriteComponent* _pSc = nullptr;

	SpriteSheet* _pSpritesheet;
};

