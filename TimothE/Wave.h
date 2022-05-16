#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Health.h"
#include <vector>

class WaveController
{
public:
	WaveController(Scene* scene);
	~WaveController();

	void SpawnWave(int difficulty);

	std::vector<GameObject*> GetEnemies();
private:
	Scene* _pCurrentScene;
	std::vector<GameObject*> _enemies;
};
