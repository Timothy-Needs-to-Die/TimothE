#pragma once
#include "WaveManager.h"
#include <cmath>
#include "SceneManager.h"
#include "FarmScene.h"
#include "GameTimeManager.h"

WaveManager::WaveManager()
{
	Scene* scene = SceneManager::GetCurrentScene();
	if (scene->GetName() == "FarmScene")
	{
		_pFarmScene = (FarmScene*)scene;
	}
}

WaveManager::~WaveManager()
{
}

void WaveManager::GenerateWave()
{
	int totalEnemies = (int)((float)_principle * pow((1.0f + (_interestRate / 1.0f)), (float)_daysPast));
	_remainingEnemies = totalEnemies;
	TIM_LOG_LOG("Day: " << _daysPast << " Amount of enemies: " << totalEnemies);
	
	for (int i = 0; i <= totalEnemies + 1; i++)
	{
		AddSpawnPosition();
	}
}

void WaveManager::Update()
{

	if (_remainingEnemies == 0 && _livingEnemies.empty()) {
		EndNight();
	}
	else {
		_timer += Time::GetDeltaTime();
		if (_timer > _currentSpawnTime) {
			_timer = 0.0f;
			SpawnEnemies();
			GenerateSpawnTime();
		}
	}
	
	
}

void WaveManager::StartNight()
{
	GenerateSpawnTime();
	GenerateWave();
}

void WaveManager::EndNight()
{
	_nightCleared = true;
	_pFarmScene->GetGameTime()->EndNight();
	_pFarmScene->GetGameTime()->StartNewDay();
}

void WaveManager::SpawnEnemies()
{
	if (_remainingEnemies == 0) return;

	//Decide how many enemies to spawn
	int partySize = rand() % _remainingEnemies;
	/*if (partySize > _remainingEnemies)
		partySize = _remainingEnemies;*/

	_remainingEnemies -= partySize;
	
	for (int i = 0; i < partySize; i++) {
		Enemy* newEnemy = new Enemy("Enemy", "ENEMY");

		//Decide spawn position
		int randomIndex = rand() % _spawnPositions.size();
		glm::vec2 position = _spawnPositions[randomIndex];
		newEnemy->GetTransform()->SetPosition(position);
		std::swap(_spawnPositions[randomIndex], _spawnPositions.back());
		_spawnPositions.pop_back();

		_livingEnemies.emplace_back(newEnemy);
		SceneManager::GetCurrentScene()->AddGameObject(newEnemy);
		TIM_LOG_LOG("Created enemy at " + std::to_string(position.x) + ", " + std::to_string(position.y));
	}

}

void WaveManager::AddSpawnPosition(glm::vec2 pos)
{
	_spawnPositions.emplace_back(pos);
}

void WaveManager::AddSpawnPosition()
{
	float maxX = 10.0f, maxY = 10.0f;
	//float x, y;
	//int side = rand() % 4;
	//switch (side)
	//{
	//case 0:
	//	// top
	//	x = (float)(rand() / (float)(RAND_MAX / maxX));
	//	y = maxY;
	//	break;
	//case 1:
	//	// right
	//	x = maxX;
	//	y = (float)(rand() / (float)(RAND_MAX / maxY));
	//	break;
	//case 2:
	//	// bottom
	//	x = (float)(rand() / (float)(RAND_MAX / maxX));
	//	y = 0.0f;
	//	break;
	//case 3:
	//	// left
	//	x = 0.0f;
	//	y = (float)(rand() / (float)(RAND_MAX / maxY));
	//	break;
	//}

	float x = (float)(rand() / (float)(RAND_MAX / maxX));
	float y = (float)(rand() / (float)(RAND_MAX / maxY));

	_spawnPositions.emplace_back(x,y);
}

void WaveManager::GenerateSpawnTime()
{
	_currentSpawnTime = rand() % _maxSpawnTime + _minSpawnTime;

}
