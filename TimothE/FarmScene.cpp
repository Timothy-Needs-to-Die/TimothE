#include "pch.h"
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

	if (!_pGameTime->IsDay()) {
		_pWaveManager->Update();
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
	else {
		_pBed->canSleepThroughNight = false;
	}

	AudioEngine::AudioUpdate(Time::GetDeltaTime());
	//Set audio Listener to player position 
	AudioEngine::Set3DListenerAttributes(FMOD_VECTOR{ _pPlayer->GetTransform()->GetPosition().x,
													_pPlayer->GetTransform()->GetPosition().y,
													0.0f }, FMOD_VECTOR{ 0.0f, 0.0f, 0.0f },
		FMOD_VECTOR{ 0.0f, 0.0f, 0.0f }, FMOD_VECTOR{ 0.0f, 0.0f, 0.0f });
}

void FarmScene::InitScene()
{
	Scene::InitScene();

	_pInventoryScreen = new InventoryScreen("InventoryScreen", "UI");
	AddGameObject(_pInventoryScreen);
	_pInventoryScreen->SetAllActive(false);

	_pGameTime = new GameTimeManager(_pLightManager);

	_pPlayer = new Player();
	_pPlayer->GetTransform()->SetPosition(_pTilemap->GetPlayerSpawn());
	AddGameObject(_pPlayer);

	_pBed = new Bed();
	_pBed->GetTransform()->SetPosition(5.0f, 3.5f);
	_pBed->GetTransform()->SetScale({ .25f, .5f });
	AddGameObject(_pBed);

	_pWoodNode = new ResourceNodeObject(Wood);
	_pWoodNode->GetTransform()->SetPosition(3.0f, 3.0f);
	AddGameObject(_pWoodNode);

	_pMetalNode = new ResourceNodeObject(Metal);
	_pMetalNode->GetTransform()->SetPosition(10.0f, 0.75f);
	AddGameObject(_pMetalNode);

	_pStoneNode = new ResourceNodeObject(Stone);
	_pStoneNode->GetTransform()->SetPosition(9.75f, 1.75f);
	AddGameObject(_pStoneNode);


	_pCoalNode = new ResourceNodeObject(Coal);
	_pCoalNode->GetTransform()->SetPosition(5.5f, 1.25f);
	AddGameObject(_pCoalNode);


	_pWaveManager = new WaveManager();

	PlayerResourceManager::LoadInCropData();


	PlayerResourceManager::GetPlantResource(WheatSeedRes)->GainResource(5);
	PlayerResourceManager::GetPlantResource(CarrotSeedRes)->GainResource(5);
	PlayerResourceManager::GetPlantResource(PotatoSeedRes)->GainResource(5);

	RegisterSounds();


	if (LoadScene("Resources/PlayerSaves/FarmSceneSaveData.sav")) {

	}
	else {

	}
	_pGameTime->StartNewDay();
	
	//std::cout << "Test 1" << std::endl;
	//_pTilemap->GenerateTileMap(10, 64, 64, 1);
	//std::cout << "Test 2" << std::endl;
	//_pTilemap->GenerateTileMap(10, 64, 64, 2);
	//std::cout << "Test 3" << std::endl;
	//_pTilemap->GenerateTileMap(10, 64, 64, 3);
	//std::cout << "Test 4" << std::endl;
	//_pTilemap->GenerateTileMap(10, 64, 64, 4);
	//std::cout << "Test 5" << std::endl;
	//_pTilemap->GenerateTileMap(10, 64, 64, 5);
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
	AudioEngine::LoadSound("BuildSound", "Resources/Sounds/SFX/PlaceBuilding.wav", AudioType::Type_SFX);
	AudioEngine::LoadSound("NightSoundTrack", "Resources/Sounds/SFX/NightTimeMusic.wav", AudioType::Type_Song);
	AudioEngine::LoadSound("FarmAmbience", "Resources/Sounds/SFX/FarmAmbience.wav", AudioType::Type_Song);
	AudioEngine::LoadSound("CashRegister", "Resources/Sounds/SFX/CashRegister.mp3", AudioType::Type_SFX);

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
	_pTilemap->SetCollidableAtPosition(object->GetTransform()->GetPosition(), true);
}

void FarmScene::RemoveStructure(StructureObject* object)
{
	for (int i = 0; i < _pStructures.size(); ++i) {
		StructureObject* pObject = _pStructures[i];

		if (pObject != object) continue;

		_pTilemap->SetCollidableAtPosition(pObject->GetTransform()->GetPosition(), false);

		_pAstarObject->UpdateNodeObstacleStatus(_pTilemap->GetTileAtWorldPos(0, pObject->GetTransform()->GetPosition())->pos, false);
		_pTilemap->SetCollidableAtPosition(object->GetTransform()->GetPosition(), false);
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

	FarmlandManager* fm = _pPlayer->GetComponent<FarmlandManager>();
	if (fm) {
		fm->OnNewDay();
	}

	Health* pHealth = _pPlayer->GetComponent<Health>();

	if (pHealth != nullptr) {
		pHealth->SetHealth(pHealth->GetMaxHealth());
	}
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
