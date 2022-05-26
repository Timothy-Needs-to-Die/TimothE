#include "GameOverScreen.h"
#include "Button.h"
#include "TextComponent.h"



GameOverScreen::GameOverScreen(std::string name, std::string tag) : GameObject(name, tag)
{
	//creates a black background image to cover screen
	AddComponent(ResourceManager::GetTexture("gameover_bg"));
	GetTransform()->SetScale({ 8.0f, 5.0f });
	

	//adds button to restart game
	//_tryAgainBTN = new GameObject("TryAgainButton","UI");
	//_tryAgainBTN->AddComponent(new Button(this));
	//_tryAgainBTN->GetComponent<Button>()->AddClickEvent(GameOverScreen::TryAgainBTNClick);

	//adds game over text
	/*_gameOverTxt = new GameObject("GameOverText", "UI");
	_gameOverTxt->AddComponent(new TextComponent(this));
	_gameOverTxt->GetComponent<TextComponent>()->SetText("Game Over");*/
	
}

//when game over retry button is pressed reset to start of day
void GameOverScreen::TryAgainBTNClick()
{
	//TO-DO restart day
	return;
}

