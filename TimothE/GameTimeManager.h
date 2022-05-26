#pragma once

class LightLevelManager;

class GameTimeManager
{
public:
	GameTimeManager(LightLevelManager* lightLevelManager) : _pLightLevelManager(lightLevelManager)
	{
		if (SceneManager::GetCurrentScene()->GetName() == "FarmScene")
		{
			_pFarmScene = (FarmScene*)SceneManager::GetCurrentScene();
		}
	}

	void Update();

	//Check if time is day.
	bool IsDay() const { return _inDay; }

	//Start new day.
	void StartNewDay();
	//Start the night.
	void StartNight();
	//End the night.
	void EndNight();

	//Set game time to night.
	void SetNight() { _dayTimer = _lengthOfDay + 1.0f; }

private:
	float _lengthOfDay = 10.0f;
	float _dayTimer = 0.0f;

	bool _inDay = true;

	class FarmScene* _pFarmScene = nullptr;
	LightLevelManager* _pLightLevelManager;
};

