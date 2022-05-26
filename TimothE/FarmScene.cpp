#include "FarmScene.h"
#include "Button.h"
#include "SpriteComponent.h"
#include "CameraManager.h"
#include "Player.h"
#include "ResourceNodeObject.h"
#include "WaveManager.h"
#include "OffensiveStructureObject.h"
#include "AIMovementCompnent.h"
#include "StructureObject.h"
#include "GameTimeManager.h"
#include "Bed.h"
#include "PlayerHealth.h"
#include "AIController.h"
#include "Enemy.h"
#include "StreamFile.h"
#include "LightsourceObject.h"
#include "TextObject.h"

#include "GameOverScreen.h"

FarmScene::~FarmScene()
{

}

void FarmScene::UpdateUI()
{

}

void FarmScene::UpdateObjects()
{
	Scene::UpdateObjects();

	_pGameTime->Update();

	if (Input::IsKeyDown(KEY_5)) {
		SceneManager::SetCurrentScene(SceneManager::CreateScene(ResourceManager::GetScene("TownScene")));
	}

	if (Input::IsKeyDown(KEY_G)) {
		//_pTilemap->AddTileAt(2, 15, 12, CameraManager::CurrentCamera());
	}
	/*if (Input::IsKeyDown(KEY_H))
	{
		if (_pPlayer != nullptr)
		{
			PlayerHealth* h = _pPlayer->GetComponent<PlayerHealth>();
			if (h != nullptr)
			{
				h->TakeDamage(50);
			}
		}
	}*/

	if (!_pGameTime->IsDay()) {
		if (Input::IsKeyDown(KEY_P)) {
			_pGameTime->EndNight();
			_pGameTime->StartNewDay();
		}
	}

	if (Input::IsKeyUp(KEY_I)) {
		_inventoryKeyPressed = false;
	}

	if (Input::IsKeyDown(KEY_I)) {
		if (_inventoryKeyPressed) return;

		_inventoryKeyPressed = true;

		bool current = _pInventoryScreen->GetAllActive();

		_pInventoryScreen->SetAllActive(!current);
		_pInventoryScreen->OnUpdate();
		//if (_pInventoryScreen == nullptr)
		//{
			//_pInventoryScreen->GetTransform()->SetPosition(50.0f, 50.0f);
			//_pInventoryScreen->GetTransform()->SetScale({ 0.25f, 0.25f });
		//}
	}

	if (Input::IsKeyDown(KEY_1)) {
		SaveScene("Resources/PlayerSaves/FarmSceneSaveData.sav");
	}
	
	if (_pPlayer->GetComponent<PlayerHealth>() != nullptr)
	{
		_pPlayer->GetComponent<TextComponent>()->SetText(std::to_string(_pPlayer->GetComponent<PlayerHealth>()->GetCurrentHealth()));
	}

	Physics::UpdateWorld();
}

void FarmScene::InitScene()
{
	Scene::InitScene();

	_pInventoryScreen = new InventoryScreen("InventoryScreen", "UI");
	AddGameObject(_pInventoryScreen);
	_pInventoryScreen->SetAllActive(false);
	
	
	//_pGameOverScreen->OnUpdate();
	//_pGameOverScreen->SetAllActive(false);

	_pSpritesheet = ResourceManager::GetSpriteSheet("testSheet");

	_pGameTime = new GameTimeManager();

	//_pStartButton = new GameObject("BUTTON", "UI");
	//_pStartButton->AddComponent(new Button(_pStartButton));
	//_pStartButton->AddComponent(new BoxColliderComponent(_pStartButton));
	//_pStartButton->AddComponent(new TextComponent(_pTestObject));
	//_pStartButton->AddComponent(ResourceManager::GetTexture("Button"));
	//_pStartButton->GetTransform()->SetPosition(0.0f, 0.0f);
	//_pStartButton->GetTransform()->SetScale({ 0.2f, 0.2f });
	//AddGameObject(_pStartButton);



	_pPlayer = new Player();
	_pPlayer->GetTransform()->SetPosition(7.0f, 3.5f);
	AddGameObject(_pPlayer);

	//_pWaveController = new WaveController(this);

	//_pDay = new Day();
	//_pDay->SetWaveController(_pWaveController);

	_pWoodNode = new ResourceNodeObject(Wood);
	_pWoodNode->GetTransform()->SetPosition(5.0f, 1.0f);
	AddGameObject(_pWoodNode);

	_pMetalNode = new ResourceNodeObject(Metal);
	_pMetalNode->GetTransform()->SetPosition(6.0, 1.0f);
	AddGameObject(_pMetalNode);

	_pStoneNode = new ResourceNodeObject(Stone);
	_pStoneNode->GetTransform()->SetPosition(7.0, 1.0f);
	AddGameObject(_pStoneNode);


	_pCoalNode = new ResourceNodeObject(Coal);
	_pCoalNode->GetTransform()->SetPosition(8.0, 1.0f);
	AddGameObject(_pCoalNode);

	farmland = new FarmlandManager("Farmland Manager");
	AddGameObject(farmland);

	//LIGHTING TEST CODE//
	_pLightManager = new LightLevelManager(_pTilemap);
	_pLightManager->SetWorldLightLevel(5);
	_pLightManager->SetMinLightLevel(1);
	_pLightManager->SetMaxLightLevel(8);


	_pBuildIndicator = new TextObject("Build Mode", "arial.ttf", "Text", "BUILDMODETEXT");
	_pBuildIndicator->GetTransform()->SetPosition({ 400.0f, 600.0f });
	_pBuildIndicator->GetTransform()->SetScale({ 1.0f, 1.0f });
	AddGameObject(_pBuildIndicator);
	_pBuildIndicator->SetActive(false);

	LoadScene("Resources/PlayerSaves/FarmSceneSaveData.sav");
}

void FarmScene::SaveScene(std::string filename)
{
	StreamFile stream;

	stream.OpenWrite(filename);

	WriteInt(stream, _pStructures.size());

	for (int i = 0; i < _pStructures.size(); ++i) {
		StructureObject* obj = _pStructures[i];

		WriteVec2(stream, obj->GetTransform()->GetPosition());

		WriteString(stream, obj->GetTag());
	}

	stream.Close();
}

void FarmScene::LoadScene(std::string filename)
{
	_pStructures.clear();

	StreamFile stream;

	stream.OpenRead(filename);

	//_pStructures.resize(ReadInt(stream));
	int size = ReadInt(stream);

	for (int i = 0; i < size; ++i) {
		StructureObject* object;

		glm::vec2 pos = ReadVec2(stream);
		std::string tag = ReadString(stream);

		if (tag == "WALL") {
			object = new StructureObject("Wall", tag);
		}
		else if (tag == "TOWER") {
			object = new OffensiveStructureObject("Tower", tag);
		}
		else if (tag == "LIGHTSOURCE") {
			object = new LightsourceObject(pos);
		}

		object->GetTransform()->SetPosition(pos);
		AddStructure(object);
	}

	stream.Close();
}

void FarmScene::AddStructure(StructureObject* object)
{
	AddGameObject(object);
	_pStructures.emplace_back(object);
	_pAstarObject->UpdateNodeObstacleStatus(_pTilemap->GetTileAtWorldPos(0, object->GetTransform()->GetPosition())->pos, true);
	_pTilemap->GetTileAtWorldPos(5, object->GetTransform()->GetPosition())->collidable = true;
}

void FarmScene::RemoveStructure(StructureObject* object)
{
	for (int i = 0; i < _pStructures.size(); ++i) {
		StructureObject* pObject = _pStructures[i];

		if (pObject != object) continue;

		_pTilemap->SetCollidableAtLayer(5, pObject->GetTransform()->GetPosition(), false);

		_pAstarObject->UpdateNodeObstacleStatus(_pTilemap->GetTileAtWorldPos(0, pObject->GetTransform()->GetPosition())->pos, false);
		_pTilemap->GetTileAtWorldPos(5, pObject->GetTransform()->GetPosition())->collidable = false;
	}

	if (object->GetTag() == "LIGHTSOURCE") {
		_pLightManager->RemoveLightSource(dynamic_cast<LightsourceObject*>(object)->GetLightSource());
	}

	std::vector<StructureObject*>::iterator it = std::find(_pStructures.begin(), _pStructures.end(), object);
	if (it != _pStructures.end()) {
		_pStructures.erase(it);
		RemoveGameObject(object);
	}
}

std::vector<class StructureObject*> FarmScene::GetStructures() const
{
	return _pStructures;
}

void FarmScene::GameOver()
{
	TIM_LOG_LOG("Game over");

	//creates game over screen
	_pGameOverScreen = new GameOverScreen();
	glm::vec2 playerPos = _pPlayer->GetTransform()->GetPosition();
	_pGameOverScreen->GetTransform()->SetPosition(playerPos.x-4, playerPos.y - 2.5); //sets position to centre on player
	AddGameObject(_pGameOverScreen);
}
