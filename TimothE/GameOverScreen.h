#include <string>
#include "GameObject.h"
#pragma once
class GameOverScreen : public GameObject
{
public:
	GameOverScreen(std::string name = "GameOverScreen", std::string tag = "UNTAGGED");
	static void TryAgainBTNClick();
private:
	GameObject* _tryAgainBTN = nullptr;
	GameObject* _gameOverTxt = nullptr;

};

