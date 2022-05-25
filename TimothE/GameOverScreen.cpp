#include "GameOverScreen.h"
#include "Button.h"
#include "TextComponent.h"



GameOverScreen::GameOverScreen(std::string name, std::string tag) : GameObject(name, tag)
{
	AddComponent(ResourceManager::GetTexture("planks"));
	GetTransform()->SetPosition(5, -0.3f);
	GetTransform()->SetScale({ 1.25f, 1.25f });
	_tryAgainBTN = AddComponent(new Button(this));
	_tryAgainBTN->AddClickEvent(GameOverScreen::TryAgainBTNClick);

	_gameOverTxt = AddComponent(new TextComponent(this));
	_gameOverTxt->SetText("Game Over");
	
}

void GameOverScreen::TryAgainBTNClick()
{
	return;
}
