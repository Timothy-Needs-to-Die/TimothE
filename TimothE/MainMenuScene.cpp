#include "MainMenuScene.h"
#include "CameraManager.h"
#include "GameTimeManager.h"
#include "TextObject.h"
#include "SceneManager.h"
#include "MainMenuUI.h"
#include "SpriteComponent.h"


void MainMenuScene::UpdateUI()
{
}

void MainMenuScene::UpdateObjects()
{
	//updates all object
	Scene::UpdateObjects();

	//if enter is pressed start game
	if (Input::IsKeyDown(KEY_ENTER)) {
		SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("FarmScene")));
	}
}

void MainMenuScene::InitScene()
{
	//initialises main menu with UI
	Scene::InitScene();
	_pMainMenuUI = new MainMenuUI();

	AddGameObject(_pMainMenuUI);
}
