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


	if (Input::IsKeyPressedOnce(KEY_I)) {
		bool current = _pInventoryScreen->GetAllActive();

		_pInventoryScreen->SetAllActive(!current);
		_pInventoryScreen->OnUpdate();
	}

	if (Input::IsKeyPressedOnce(KEY_O)) {
		SceneManager::SetCurrentScene("EastPlains");
	}

	if (Input::IsKeyPressedOnce(KEY_P)) {
		glm::vec2 mapDimensions = _pTilemap->GetTileMapDimensions();

		//for (int i = 0; i < 100; i++) {
		//	Enemy* pEnemy = _pEnemyStress[i];
		//
		//	int randX = rand() % (int)mapDimensions.x;
		//	int randY = rand() % (int)mapDimensions.y;
		//
		//	float xPos = randX * 0.25f;
		//	float yPos = randY * 0.25f;
		//
		//	if (xPos == _pTilemap->GetMapSize().x) {
		//		xPos -= 0.25f;
		//	}
		//	if (yPos == _pTilemap->GetMapSize().y) {
		//		yPos -= 0.25f;
		//	}
		//
		//	pEnemy->GetComponent<AIMovementCompnent>()->SetDestination({ xPos, yPos });
		//}
	}


	if (_pInventoryScreen->GetAllActive())
	{
		_pInventoryScreen->OnUpdate();
	}

	Physics::UpdateWorld();

	if (Input::IsKeyPressedOnce(KEY_LEFT_SHIFT)) {
		CameraManager::MainCamera()->SetZoomLevel(1.5f);
	}

	if (Input::IsKeyPressedOnce(KEY_RIGHT_SHIFT)) {
		CameraManager::MainCamera()->SetZoomLevel(2.5f);
	}


	AudioEngine::AudioUpdate(Time::GetDeltaTime());
	//Set audio Listener to player position 
	AudioEngine::Set3DListenerAttributes(FMOD_VECTOR{ _pPlayer->GetTransform()->GetPosition().x,
													_pPlayer->GetTransform()->GetPosition().y,
													0.0f }, FMOD_VECTOR{ 0.0f, 0.0f, 0.0f },
		FMOD_VECTOR{ 0.0f, 0.0f, 0.0f }, FMOD_VECTOR{ 0.0f, 0.0f, 0.0f });
}

void FarmScene::InitScene(bool hasPlayer)
{
	Scene::InitScene(hasPlayer);
	

	_pInventoryScreen = new InventoryScreen("InventoryScreen", "UI");
	AddGameObject(_pInventoryScreen);
	_pInventoryScreen->SetAllActive(false);

	_pGameTime = new GameTimeManager(_pLightManager);

	_pWoodNode = new ResourceNodeObject(CoreResourceType::Wood);
	_pWoodNode->GetTransform()->SetPosition(3.0f, 3.0f);
	AddGameObject(_pWoodNode);

	_pWaveManager = new WaveManager();

	GameObject* buttonGO = new GameObject("buttonGO", "UI");
	SpriteComponent* sc = buttonGO->AddComponent(new SpriteComponent(buttonGO, 200));

	sc->SetSprite(ResourceManager::GetSpriteSheet("campfire")->GetSpriteAtIndex(0));


	Button* pButton = new Button(buttonGO);

	buttonGO->AddComponent(pButton);

	buttonGO->GetTransform()->SetPosition(935.0f, 100.0f);
	buttonGO->GetTransform()->SetScale({ 50.f, 50.0f });


	AddGameObject(buttonGO);

	PlayerResourceManager::LoadInCropData();
	PlayerResourceManager::GetPlantResource(WheatSeedRes)->GainResource(5);
	PlayerResourceManager::GetPlantResource(CarrotSeedRes)->GainResource(5);
	PlayerResourceManager::GetPlantResource(PotatoSeedRes)->GainResource(5);

	RegisterSounds();

	//CameraManager::MainCamera()->SetZoomLevel(1.5f);

	//if (LoadScene("Resources/PlayerSaves/FarmSceneSaveData.sav")) {
	//
	//}
	//else {
	//
	//}

	_pGameTime->StartNewDay();

	//int*** map = _pTilemap->GenerateTileMap(10, 64, 64, 3);
	//_pTilemap->CreateTilemapFromProcGen(map, 64, 64, "dungeonGrey");
	_pPlayer->GetTransform()->SetPosition(_pTilemap->GetPlayerSpawn());


	for (int i = 0; i < 100; i++) {
		Enemy* pEnemy = new Enemy();

		_pEnemyStress.emplace_back(pEnemy);
		AddGameObject(pEnemy);
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
		StructureObject* pObject = nullptr;

		glm::vec2 pos = ReadVec2(stream);
		std::string tag = ReadString(stream);

		if (tag == "WALL") {
			pObject = new StructureObject("Wall", tag);
		}
		else if (tag == "TOWER") {
			pObject = new OffensiveStructureObject("Tower", tag);
		}
		else if (tag == "LIGHTSOURCE") {
			pObject = new LightsourceObject(pos);
		}

		if (pObject != nullptr) {
			pObject->GetTransform()->SetPosition(pos);
			AddStructure(pObject);
		}
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
	_pGameOverScreen->GetTransform()->SetPosition(playerPos.x - 4.0f, playerPos.y - 2.5f); //sets position to centre on player
	AddGameObject(_pGameOverScreen);
}
