#include "GameTimeManager.h"
#include "Time.h"
#include "Core.h"
#include "SceneManager.h"
#include "FarmScene.h"
#include "WaveManager.h"
#include "LightLevelManager.h"

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
	AudioEngine::PlaySound("RoosterSound", 60, 70, 1, 1);
	AudioEngine::PlaySound("FarmAmbience", 30, 40, 1, 1);
	_pLightLevelManager->SetWorldLightLevel(5);
}

void GameTimeManager::StartNight()
{
	AudioEngine::PlaySound("NightSoundTrack", 55, 60, 1, 1);
	_dayTimer = 0.0f;
	_inDay = false;
	
	_pLightLevelManager->SetWorldLightLevel(1);

	FarmScene* scene = (FarmScene*)SceneManager::GetCurrentScene();
	scene->GetWaveManager()->StartNight();

	TIM_LOG_LOG("Night Time");
}

void GameTimeManager::EndNight()
{
}
