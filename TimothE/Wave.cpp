#include "Wave.h"
#include "CSVReader.h"
#include "Scene.h"

WaveController::WaveController(Scene* scene) : _pCurrentScene(scene)
{
}

WaveController::~WaveController()
{
	_enemies.clear();
}

bool WaveController::TryNewWave()
{
	if (_remainingWaves > 0)
	{
		if (_enemies.size() == 0)
		{
			_remainingWaves--;
			_enemyCount += _enemyIncreaseRate;
			SpawnWave();
			return true;
		}
	}
	return false;
}

void WaveController::StartWaves(int waveCount, int initialEnemies, int increaseRate)
{
	_remainingWaves = waveCount;
	_enemyCount = initialEnemies;
	_enemyIncreaseRate = increaseRate;
	SpawnWave();
}

void WaveController::StartWaves(int day)
{
	std::vector<std::vector<std::string>> waveConfig = CSVReader::RequestDataFromFile("Resources/Data/WaveConfig.csv");
	if (waveConfig.size() == 0)
	{
		return;
	}

	bool foundDay = false;
	for (int i = 0; i < waveConfig.size(); i++)
	{
		if (std::stoi(waveConfig[i][0]) == day)
		{
			foundDay = true;
			_remainingWaves = std::stoi(waveConfig[i][1]);
			_enemyCount = std::stoi(waveConfig[i][2]);
			_enemyIncreaseRate = std::stoi(waveConfig[i][3]);
			break;
		}
	}
	if (!foundDay)
	{
		// if greater than the final day in config, set to the final day
		int i = waveConfig.size() - 1;
		_remainingWaves = std::stoi(waveConfig[i][1]);
		_enemyCount = std::stoi(waveConfig[i][2]);
		_enemyIncreaseRate = std::stoi(waveConfig[i][3]);
	}
	SpawnWave();
}

void WaveController::SpawnWave()
{
	_enemies.clear();

	for (int i = 0; i < _enemyCount; i++)
	{
		_enemies.push_back(new GameObject("Enemy", "ENEMY"));
		// todo change the texture
		_enemies[i]->AddComponent<Texture2D>(ResourceManager::GetTexture("whiteTexture"));

		// spawn on random edge
		//glm::vec2 tilesize = _pCurrentScene->GetTileMap()->GetTileSize();

		float x = 0.0f;
		float y = 0.0f;
		float maxX = 10.0f;
		float maxY = 10.0f;

		int side = rand() % 4;
		switch (side)
		{
		case 0:
			// top
			x = (float)(rand() / (float)(RAND_MAX / maxX));
			y = maxY;
			break;
		case 1:
			// right
			x = maxX;
			y = (float)(rand() / (float)(RAND_MAX / maxY));
			break;
		case 2:
			// bottom
			x = (float)(rand() / (float)(RAND_MAX / maxX));
			y = 0.0f;
			break;
		case 3:
			// left
			x = 0.0f;
			y = (float)(rand() / (float)(RAND_MAX / maxY));
			break;
		}

		_enemies[i]->GetTransform()->SetPosition(x, y);
		_enemies[i]->GetTransform()->SetScale({ 0.25f, 0.45f });
		Health* h = new Health(_enemies[i], 20);
		h->SetMaxHealth(50);
		_enemies[i]->AddComponent(h);
		_pCurrentScene->AddGameObject(_enemies[i]);
	}
	std::cout << "Created " << _enemies.size() << " enemies" << std::endl;
}

std::vector<GameObject*> WaveController::GetEnemies()
{
	return _enemies;
}
