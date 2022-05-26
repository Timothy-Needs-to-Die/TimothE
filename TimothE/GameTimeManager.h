#pragma once

class LightLevelManager;

class GameTimeManager
{
public:
	GameTimeManager(LightLevelManager* lightManager) : _pLightLevelManager(lightManager)
	{

	}

	void Update();

	bool IsDay() const { return _inDay; }

	void StartNewDay();
	void EndNight();

private:
	float _lengthOfDay = 10.0f;
	float _dayTimer = 0.0f;

	bool _inDay = true;

	LightLevelManager* _pLightLevelManager;
};

