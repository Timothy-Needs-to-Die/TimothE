#include "GameTimeManager.h"
#include "Time.h"
#include "Core.h"
#include "SceneManager.h"
#include "FarmScene.h"
#include "WaveManager.h"

GameTimeManager::GameTimeManager()
{
	if (SceneManager::GetCurrentScene()->GetName() == "FarmScene")
	{
		_pFarmScene = (FarmScene*)SceneManager::GetCurrentScene();
	}
}

void GameTimeManager::Update()
{
	if (!_inDay) return;

	_dayTimer += Time::GetDeltaTime();

	if (_dayTimer > _lengthOfDay) {
		StartNight();
	}

}

void GameTimeManager::StartNewDay()
{
	_dayTimer = 0.0f;
	_inDay = true;
}

void GameTimeManager::StartNight()
{
	_dayTimer = 0.0f;
	_inDay = false;

	FarmScene* scene = (FarmScene*)SceneManager::GetCurrentScene();
	scene->GetWaveManager()->StartNight();

	TIM_LOG_LOG("Night Time");
}

void GameTimeManager::EndNight()
{
}
