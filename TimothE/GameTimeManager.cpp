#include "GameTimeManager.h"
#include "Time.h"
#include "Core.h"
#include "LightLevelManager.h"

void GameTimeManager::Update()
{
	if (!_inDay) return;


	_dayTimer += Time::GetDeltaTime();

	if (_dayTimer > _lengthOfDay) {
		_dayTimer = 0.0f;
		_inDay = false;

		_pLightLevelManager->SetWorldLightLevel(2);

		TIM_LOG_LOG("Night Time");
	}

}

void GameTimeManager::StartNewDay()
{
	_dayTimer = 0.0f;
	_inDay = true;
}

void GameTimeManager::EndNight()
{
	TIM_LOG_LOG("Night is over");
}
