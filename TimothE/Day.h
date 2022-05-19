#pragma once
#include "Time.h"

class Day
{
public:
	Day();
	~Day();

	void Update();

	void SetDay(bool day) { _isDaytime = day; }
	bool IsDay() { return _isDaytime; }

	// returns true on the first frame that it turns night
	bool NightStart();

	void SetDayLength(float length) { _dayLength = length; }
	float GetDayLength() { return _dayLength; }

	void SetTime(float time) { _currentTime = time; }
	float GetTime() { return _currentTime; }

	int GetDayCount() { return _dayCount; }

private:
	float _dayLength = 5.0f;
	float _currentTime;
	bool _isDaytime;
	bool _oldDaytime;

	int _dayCount;
};

