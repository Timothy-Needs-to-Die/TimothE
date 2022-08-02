#include "pch.h"
#include "TownScene.h"
#include "SceneManager.h"

void TownScene::UpdateUI()
{

}

void TownScene::UpdateObjects()
{
	if (Input::IsKeyPressedOnce(KEY_4)) {
		SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("FarmScene")));
	}
}

void TownScene::InitScene(bool hasPlayer)
{
	Scene::InitScene(hasPlayer);
}
