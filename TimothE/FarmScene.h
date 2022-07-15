#pragma once
#include "Scene.h"
#include "SpriteComponent.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "Fighter.h"
#include "Health.h"
#include "InventoryScreen.h"

#include "ResourceNode.h"
#include "FarmlandManager.h"
#include "PlantResourceType.h"
#include "Button.h"
#include "CameraManager.h"
#include "LightLevelManager.h"
#include "AudioEngine.h"

class FarmScene : public Scene
{
public:

	FarmScene(std::string name) : Scene(name)
	{

	}

	~FarmScene();

	void UpdateUI() override;
	void UpdateObjects() override;
	void InitScene() override;

	void SaveScene(std::string filename);
	bool LoadScene(std::string filename);

	void AddStructure(class StructureObject* object);
	void RemoveStructure(class StructureObject* object);
	std::vector<class StructureObject*> GetStructures() const;

	void PlayerSlept();
	void GameOver() override;

	class GameTimeManager* GetGameTime() { return _pGameTime; }

	class WaveManager* GetWaveManager() const { return _pWaveManager; }

	void RegisterSounds();
private:
	class Player* _pPlayer;
	class ResourceNodeObject* _pWoodNode = nullptr;
	class GameTimeManager* _pGameTime = nullptr;
	class Bed* _pBed;
	class InventoryScreen* _pInventoryScreen = nullptr;
	class GameOverScreen* _pGameOverScreen = nullptr;
	class FarmlandManager* farmland;
	class WaveManager* _pWaveManager;

	//Farmland

	std::vector<class StructureObject*> _pStructures;

	bool farmKeyPressed = false;
	bool _inventoryKeyPressed = false;
	bool spawnEnemyKey = false;
};
