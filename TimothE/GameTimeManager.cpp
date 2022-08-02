#include "pch.h"
#include "GameTimeManager.h"
#include "Time.h"
#include "Core.h"
#include "SceneManager.h"
#include "FarmScene.h"
#include "WaveManager.h"
#include "LightLevelManager.h"
#include "Core/Graphics/Window.h"

void GameTimeManager::Update()
{
	if (!_inDay) return;

	_currentDayTimer += Time::GetDeltaTime();

	if (_currentDayTimer > _lengthOfDay) {
		StartNight();
	}
}

void GameTimeManager::StartNewDay()
{
	Window::SetWindowColour(0.0f, 0.0f, 0.0f, 1.0f);
	_currentDayTimer = 0.0f;
	_inDay = true;
	AudioEngine::PlaySound("RoosterSound", 60, 70, 1, 1);
	AudioEngine::PlaySound("FarmAmbience", 2, 2, 1, 1);
	_pLightLevelManager->SetWorldLightLevel(5);
}

void GameTimeManager::StartNight()
{
	AudioEngine::PlaySound("NightSoundTrack", 55, 60, 1, 1);
	_currentDayTimer = 0.0f;
	_inDay = false;
	
	_pLightLevelManager->SetWorldLightLevel(1);

	FarmScene* scene = (FarmScene*)SceneManager::GetCurrentScene();
	

	TIM_LOG_LOG("Night Time");
}

void GameTimeManager::EndNight()
{
	ProgressDay();
}

void GameTimeManager::ProgressDay()
{
	if (_currentDay == (84 * _currentYear))
	{
		ProgressYear();
	}
	if (_currentDayOfWeek == Days::Sunday) {
		ProgressWeek();
	}
	_currentDay++;
	
}

void GameTimeManager::ProgressWeek()
{
	_currentWeekOfMonth++;
	if (_currentWeekOfMonth == 1) {
		_currentSeasonPhase == SeasonPhase::Early;
	}
	else if (_currentWeekOfMonth == 2) {
		_currentSeasonPhase == SeasonPhase::Mid;
	}
	else if (_currentWeekOfMonth == 3) {
		_currentSeasonPhase == SeasonPhase::Late;
	}
	else if (_currentWeekOfMonth == 4) {
		ProgressSeason();
	}
		
}

void GameTimeManager::ProgressSeason()
{
	_currentWeekOfMonth = 1;
	switch (_currentSeason)
	{
	case Spring:
		_currentSeason = SeasonType::Summer;
		_lengthOfDay = 600;
		break;
	case Summer:
		_currentSeason = SeasonType::Autumn;
		_lengthOfDay = 540;
		break;
	case Autumn:
		_currentSeason = SeasonType::Winter;
		_lengthOfDay = 480;
		break;
	case Winter:
		_currentSeason = SeasonType::Spring;
		_lengthOfDay = 540;
		break;
	default:
		_currentSeason == SeasonType::Spring;
		break;
	}

	TIM_LOG_LOG("Season Changed to: " << _currentSeason);
}

void GameTimeManager::ProgressYear()
{
	_currentYear++;
}

void GameTimeManager::GameTimeToString()
{
}

void GameTimeManager::LoadTimeFromString()
{
}

SeasonPhase GameTimeManager::CheckSeasonPhase()
{
	return _currentSeasonPhase;
}
