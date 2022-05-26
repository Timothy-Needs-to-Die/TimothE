#pragma once
#include "WaveManager.h"
#include <cmath>

WaveManager::WaveManager()
{
}

WaveManager::~WaveManager()
{
}

void WaveManager::GenerateWave()
{
	int totalEnemies = (int)((float)_principle * pow((1.0f + (_interestRate / 1.0f)), (float)_daysPast));
	_remainingEnemies = totalEnemies;
	TIM_LOG_LOG("Day: " << _daysPast << " Amount of enemies: " << totalEnemies);

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
	
}

void WaveManager::SpawnEnemies()
{
	if (_remainingEnemies == 0) return;
	//Decide how many enemies to spawn
	int partySize = rand() % 1 + _maxPartySize;
	if (partySize > _remainingEnemies)
		partySize = _remainingEnemies;

	_remainingEnemies -= partySize;

	//Decide spawn position
	int randomIndex = rand() % _spawnPositions.size();
	glm::vec2 position = _spawnPositions[randomIndex];

	
	for (int i = 0; i < partySize; i++) {
		Enemy* newEnemy = new Enemy("Enemy", "ENEMY");
		newEnemy->GetTransform()->SetPosition(position);
		_livingEnemies.emplace_back(newEnemy);
	}

}

void WaveManager::AddSpawnPosition(glm::vec2 pos)
{
	_spawnPositions.emplace_back(pos);
}

bool WaveManager::GetWaveCleared()
{
	return _nightCleared;
}

void WaveManager::GenerateSpawnTime()
{
	_currentSpawnTime = rand() % _maxSpawnTime + _minSpawnTime;

}
