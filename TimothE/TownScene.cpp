#include "TownScene.h"

void TownScene::UpdateUI()
{

}

void TownScene::UpdateObjects()
{
	Scene::UpdateObjects();
}

void TownScene::InitScene()
{
	_pTilemap = new TileMap(_name);
}
