#include "pch.h"
#include "MainMenuScene.h"
#include "CameraManager.h"
#include "GameTimeManager.h"
#include "TextObject.h"
#include "SceneManager.h"
#include "MainMenuUI.h"
#include "SpriteComponent.h"
#include "Player.h"

void MainMenuScene::UpdateUI()
{
}

void MainMenuScene::UpdateObjects()
{
	//updates all object
	Scene::UpdateObjects();

	//if enter is pressed start game
	if (Input::IsKeyPressedOnce(KEY_ENTER)) {
		SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("FarmScene")));
	}
}


void MainMenuScene::InitScene(bool hasPlayer)
{
	//initialises main menu with UI
	Scene::InitScene(false);
	_pMainMenuUI = new MainMenuUI();
	AddGameObject(_pMainMenuUI);
}
