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

void EastPlainsScene::InitScene(bool hasPlayer)
{
	Scene::InitScene(hasPlayer);
	_pPlayer->GetTransform()->SetPosition(_pTilemap->GetPlayerSpawn());
	

	CameraManager::MainCamera()->SetFollowTarget(_pPlayer);
	CameraManager::MainCamera()->SetTileMap(_pTilemap);
	CameraManager::MainCamera()->RecalculateViewMatrix();
}
