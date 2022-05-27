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

	//if (Input::IsKeyDown(KEY_G)) {
	//	_pTilemap->AddTileAt(2, 15, 12, CameraManager::CurrentCamera());
	//}

	if (_pGameTime->IsDay()) {
		if (Input::IsKeyDown(KEY_O)) {
			_pGameTime->StartNight();
		}
	}
	else {
		_pWaveManager->Update();

		if (Input::IsKeyDown(KEY_P)) {
			_pGameTime->EndNight();
			_pGameTime->StartNewDay();
			// Tell the farmland that a new day has dawned
			_pPlayer->GetComponent<FarmlandManager>()->OnNewDay();
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
	}




	if (_pInventoryScreen->GetAllActive())
	{
		_pInventoryScreen->OnUpdate();
	}

	Physics::UpdateWorld();

	if (_pWaveManager->GetWaveCleared())
	{
		_pBed->canSleepThroughNight = true;
	}

}

void FarmScene::InitScene()
{
	Scene::InitScene();

	_pInventoryScreen = new InventoryScreen("InventoryScreen", "UI");
	AddGameObject(_pInventoryScreen);
	_pInventoryScreen->SetAllActive(false);

	_pGameTime = new GameTimeManager(_pLightManager);

	_pPlayer = new Player();
	_pPlayer->GetTransform()->SetPosition(7.0f, 3.5f);
	AddGameObject(_pPlayer);

	_pBed = new Bed();
	_pBed->GetTransform()->SetPosition(5.0f, 3.5f);
	_pBed->GetTransform()->SetScale({ .25f, .5f });
	AddGameObject(_pBed);

	//_pWaveController = new WaveController(this);

	//_pDay = new Day();
	//_pDay->SetWaveController(_pWaveController);

	_pWoodNode = new ResourceNodeObject(Wood);
	_pWoodNode->GetTransform()->SetPosition(5.0f, 1.0f);
	AddGameObject(_pWoodNode);

	_pMetalNode = new ResourceNodeObject(Metal);
	_pMetalNode->GetTransform()->SetPosition(8.25f, 1.25f);
	AddGameObject(_pMetalNode);

	_pStoneNode = new ResourceNodeObject(Stone);
	_pStoneNode->GetTransform()->SetPosition(7.5, 0.75f);
	AddGameObject(_pStoneNode);


	_pCoalNode = new ResourceNodeObject(Coal);
	_pCoalNode->GetTransform()->SetPosition(7.75f, 1.25f);
	AddGameObject(_pCoalNode);


	_pWaveManager = new WaveManager();

	PlayerResourceManager::LoadInCropData();

	RegisterSounds();

	if (LoadScene("Resources/PlayerSaves/FarmSceneSaveData.sav")) {

	}else{
		PlayerResourceManager::GetPlantResource(WheatSeedRes)->GainResource(5);
		PlayerResourceManager::GetPlantResource(CarrotSeedRes)->GainResource(5);
		PlayerResourceManager::GetPlantResource(PotatoSeedRes)->GainResource(5);
	}

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


void FarmScene::RegisterSounds()
{
	AudioEngine::LoadSound("StoneMine", "Resources/Sounds/SFX/StoneHit.mp3", AudioType::Type_SFX);
	AudioEngine::LoadSound("WoodChop", "Resources/Sounds/SFX/WoodChop.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("PlantSeed", "Resources/Sounds/SFX/PlantSeed.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("FootStep", "Resources/Sounds/SFX/SingleFootsep.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("SwordSlash", "Resources/Sounds/SFX/SwordSlash.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("Rooster", "Resources/Sounds/SFX/Rooster.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("EnemyHit", "Resources/Sounds/SFX/EnemyHit.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("BuildSound", "Resources/Sounds/SFX/BuildSound.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("NightSoundTrack", "Resources/Sounds/SFX/NightTimeMusic.wav", AudioType::Type_Song);

}


bool FarmScene::LoadScene(std::string filename)
{
	_pStructures.clear();

	StreamFile stream;

	bool result = stream.OpenRead(filename);

	if (!result) return false;

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

	return true;
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

void FarmScene::PlayerSlept()
{
	SaveScene("Resources/PlayerSaves/FarmSceneSaveData.sav");
	_pGameTime->EndNight();
	_pGameTime->StartNewDay();
}

void FarmScene::GameOver()
{
	TIM_LOG_LOG("Game over");

	//creates game over screen
	_pGameOverScreen = new GameOverScreen();
	glm::vec2 playerPos = _pPlayer->GetTransform()->GetPosition();
	_pGameOverScreen->GetTransform()->SetPosition(playerPos.x - 4, playerPos.y - 2.5); //sets position to centre on player
	AddGameObject(_pGameOverScreen);
}
