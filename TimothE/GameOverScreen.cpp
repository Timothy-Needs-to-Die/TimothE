#include "pch.h"
#include "GameOverScreen.h"
#include "Button.h"
#include "TextComponent.h"
#include "SceneManager.h"
#include "FarmScene.h"


GameOverScreen::GameOverScreen(std::string name, std::string tag) : GameObject(name, tag)
{
	//creates a black background image to cover screen
	//AddComponent(ResourceManager::GetTexture("gameover_bg"));
	GetTransform()->SetScale({ 8.0f, 5.0f });


	//adds button to restart game
	_tryAgainBTN = new GameObject("TryAgainButton", "UI");
	_tryAgainBTN->AddComponent(new Button(_tryAgainBTN));
	_tryAgainBTN->GetComponent<TextComponent>()->SetText("Try Again");
	//_tryAgainBTN->GetComponent<BoxColliderComponent>()->SetScale(100);
	_tryAgainBTN->GetComponent<Button>()->AddClickEvent(GameOverScreen::TryAgainBTNClick);
	_tryAgainBTN->GetTransform()->SetPosition(300,300);
	_tryAgainBTN->GetTransform()->SetScale({ 10050.0f, 10050.0f });
	SceneManager::GetCurrentScene()->AddGameObject(_tryAgainBTN);
	

	//adds game over text
	_gameOverTxt = new GameObject("GameOverText", "UI");
	_gameOverTxt->AddComponent(new TextComponent(_gameOverTxt));
	_gameOverTxt->GetComponent<TextComponent>()->SetText("Game Over");
	
}

//when game over retry button is pressed reset to start of day
void GameOverScreen::TryAgainBTNClick()
{
	FarmScene* fs = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());
	if (fs) {
		SceneManager::SetCurrentScene(SceneManager::GetScene("FarmScene"));
	}
}

