#include "TownScene.h"
#include "SceneManager.h"

void TownScene::UpdateUI()
{

}

void TownScene::UpdateObjects()
{
	if (Input::IsKeyDown(KEY_4)) {
		SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("FarmScene")));
	}
}

void TownScene::InitScene()
{
	Scene::InitScene();
}
