#pragma once
#include "Scene.h"
#include "PlayerMovement.h"

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

	AnimatedSpritesheet* _pAnimSheet;

	SpriteSheet* _pSpritesheet;
};

