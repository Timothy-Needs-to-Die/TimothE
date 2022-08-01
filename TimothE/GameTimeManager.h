#pragma once
#include "SceneManager.h"
#include "GameTimeStructures.h"

class LightLevelManager;

class GameTimeManager
{
public:
	GameTimeManager(LightLevelManager* lightLevelManager) : _pLightLevelManager(lightLevelManager)
	{
		/*if (SceneManager::GetCurrentScene()->GetName() == "FarmScene")
		{
			_pFarmScene = (FarmScene*)SceneManager::GetCurrentScene();
		}*/

	}

	void Update();

	//Check if time is day.
	bool IsDay() const { return _inDay; }

	void StartNewDay();
	void StartNight();
	void EndNight();

	void ProgressDay();
	void ProgressWeek();
	void ProgressSeason();
	void ProgressYear();

	void GameTimeToString();
	void LoadTimeFromString();
	SeasonPhase CheckSeasonPhase();

	//Set game time to night.
	void SetNight() { _currentDayTimer = _lengthOfDay + 1.0f; }

private:

	int _currentDay = 1;
	Days _currentDayOfWeek;
	int _currentYear = 1;
	float _currentDayTimer = 0.0f;
	int _currentWeekOfMonth = 1;

	SeasonPhase _currentSeasonPhase;
	SeasonType _currentSeason;


	float _lengthOfDay = 180.0f;

	bool _inDay = true;
	
	LightLevelManager* _pLightLevelManager;
};

