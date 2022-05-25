#include <string>
#include "GameObject.h"
#pragma once
class GameOverScreen : public GameObject
{
public:
	GameOverScreen(std::string name = "New Character", std::string tag = "UNTAGGED");
	static void TryAgainBTNClick();
private:
	class Button* _tryAgainBTN = nullptr;
	class TextComponent* _gameOverTxt = nullptr;

};

