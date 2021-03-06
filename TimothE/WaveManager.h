#pragma once
#include <vector>
#include "Enemy.h"
#include "glm.hpp"
#include "Time.h"

class WaveManager
{
public:
	WaveManager();
	~WaveManager();

	void RemoveEnemyFromAliveList(Enemy* enemy);
	void GenerateWave();
	void Update();
	void StartNight();
	void SpawnEnemies();
	void AddSpawnPosition(glm::vec2 pos);
	void AddSpawnPosition();
	bool GetWaveCleared();
	
	int _daysPast = 0;
private:
	void GenerateSpawnTime();

	bool _isNight = false;
	bool _nightCleared = false; 
	float _interestRate = 0.12f;
	float _principle = 10.0f;
	int _minSpawnTime = 0;
	int _maxSpawnTime = 5;
	float _currentSpawnTime;
	float _timer;

	int _remainingEnemies;
	std::vector<Enemy*> _livingEnemies;
	std::vector<glm::vec2> _spawnPositions; 

	class FarmScene* _pFarmScene;
	
};

