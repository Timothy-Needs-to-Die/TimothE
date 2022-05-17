#pragma once

#include "Scene.h"
#include "Wave.h"
//class Scene;
class PlayerInputComponent;
class SpriteComponent;
class AnimatedSpriteSheet;
class MovementComponentl;
class Fighter;
class Health;
//class Wave;

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


	//class PlayerInputComponent* _pPlayerMovement = nullptr;
	//GameObject* _pPlayerObject = nullptr;
	//Health* _pPlayerHealth = nullptr;

	SpriteSheet* _pSpritesheet;


	WaveController* _pWaveController = nullptr;

	class Player* _pPlayer;
};

