#pragma once
#include "Time.h"

class Day
{
public:
	Day();
	~Day();

	void Update();

	void SetDay(bool day) { _day = day; }
	bool IsDay() { return _day; }

	// returns true on the first frame that it turns night
	bool NightStart();

	void SetDayLength(float length) { _dayLength = length; }
	float GetDayLength() { return _dayLength; }

	void SetTime(float time) { _currentTime = time; }
	float GetTime() { return _currentTime; }

private:
	float _dayLength = 5.0f;
	float _currentTime;
	bool _day;
	bool _oldDay;
};

