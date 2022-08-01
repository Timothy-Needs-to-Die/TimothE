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

	if (Input::IsKeyDown(KEY_O)) {
		SceneManager::SetCurrentScene("FarmScene");
	}
}

void EastPlainsScene::InitScene()
{
	Scene::InitScene();
	_pPlayer = new Player();
	_pPlayer->GetTransform()->SetPosition(_pTilemap->GetPlayerSpawn());
	AddGameObject(_pPlayer);

	CameraManager::MainCamera()->SetFollowTarget(_pPlayer);
	CameraManager::MainCamera()->SetTileMap(_pTilemap);
	CameraManager::MainCamera()->RecalculateViewMatrix();
}
