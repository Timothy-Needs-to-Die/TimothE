#pragma once

#include "GameObject.h"
#include "Health.h"
#include <vector>

class WaveController
{
public:
	WaveController(Scene* scene);
	~WaveController();

	bool TryNewWave();

	/// <summary>
	/// Start spawning waves
	/// </summary>
	/// <param name="waveCount"> How many waves until it's over </param>
	/// <param name="initialEnemies"> How many enemies to spawn in first wave </param>
	/// <param name="increaseRate"> How many enemies to increase by with each wave</param>
	void StartWaves(int waveCount, int initialEnemies, int increaseRate);

	/// <summary>
	/// Loads the config CSV to get values for wavecount, initialenemies, increaserate 
	/// </summary>
	void StartWaves(int day);

	std::vector<GameObject*> GetEnemies();
private:
	void SpawnWave();

	class Scene* _pCurrentScene;
	std::vector<GameObject*> _enemies;

	int _remainingWaves = 0;
	int _enemyCount = 0;
	int _enemyIncreaseRate = 0;
};
