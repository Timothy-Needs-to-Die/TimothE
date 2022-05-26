#pragma once

class LightLevelManager;

class GameTimeManager
{
public:
	GameTimeManager(LightLevelManager* lightLevelManager) : _pLightLevelManager(lightLevelManager)
	{

	}

	void Update();

	bool IsDay() const { return _inDay; }

	void StartNewDay();
	void EndNight();
	void SetNight() { _dayTimer = _lengthOfDay + 1.0f; }

private:
	float _lengthOfDay = 10.0f;
	float _dayTimer = 0.0f;

	bool _inDay = true;

	LightLevelManager* _pLightLevelManager;
};

