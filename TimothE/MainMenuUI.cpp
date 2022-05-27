#include "MainMenuUI.h"
#include "Button.h"
#include "TextComponent.h"
#include "SceneManager.h"

MainMenuUI::MainMenuUI(std::string name, std::string tag) : GameObject(name, tag)
{
	//creates a black background image to cover screen
	AddComponent(ResourceManager::GetTexture("gameover_bg"));
	GetTransform()->SetPosition({ -4, -2.0f });
	GetTransform()->SetScale({ 800.0f, 500.0f });



	//adds press to play
	_pPressToPlay = new GameObject("PressToPlay", "UI");
	_pPressToPlay->AddComponent(new TextComponent(_pPressToPlay));
	_pPressToPlay->GetComponent<TextComponent>()->SetText("Press Enter To Play");
	_pPressToPlay->GetComponent<TextComponent>()->_scale = .85;
	_pPressToPlay->GetTransform()->SetPosition(750, 500);
	SceneManager::GetCurrentScene()->AddGameObject(_pPressToPlay);

	//adds game title
	_pTitle = new GameObject("Title", "UI");
	_pTitle->AddComponent(new TextComponent(_pTitle));
	_pTitle->GetComponent<TextComponent>()->SetText("Timothy Needs To Die");
	_pTitle->GetComponent<TextComponent>()->_scale = 1.5;
	_pTitle->GetTransform()->SetPosition(600, 900);
	SceneManager::GetCurrentScene()->AddGameObject(_pTitle);

	//adds company logo
	_pLogo = new GameObject("Logo", "UI");
	_pLogo->AddComponent(new TextComponent(_pLogo));
	_pLogo->GetComponent<TextComponent>()->SetText("ThymotheE Engine");
	_pLogo->GetComponent<TextComponent>()->_scale = .4;
	_pLogo->GetTransform()->SetPosition(100, 100);
	SceneManager::GetCurrentScene()->AddGameObject(_pLogo);

	//adds credits
	_pMadeBy = new GameObject("Credits", "UI");
	_pMadeBy->AddComponent(new TextComponent(_pMadeBy));
	_pMadeBy->GetComponent<TextComponent>()->SetText("By Timothy Needs To Die Team");
	_pMadeBy->GetComponent<TextComponent>()->_scale = .4;
	_pMadeBy->GetTransform()->SetPosition(1550, 100);
	SceneManager::GetCurrentScene()->AddGameObject(_pMadeBy);

}




