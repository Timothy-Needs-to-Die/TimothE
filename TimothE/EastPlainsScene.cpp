#include "EastPlainsScene.h"
#include "Player.h"
#include "SceneManager.h"
#include "CameraManager.h"

EastPlainsScene::~EastPlainsScene()
{

}

void EastPlainsScene::UpdateUI()
{

}

void EastPlainsScene::UpdateObjects()
{
	Scene::UpdateObjects();

	if (Input::IsKeyPressedOnce(KEY_O)) {
		SceneManager::SetCurrentScene("FarmScene");
	}
}

void EastPlainsScene::InitScene(bool hasPlayer)
{
	Scene::InitScene(hasPlayer);
	
}
