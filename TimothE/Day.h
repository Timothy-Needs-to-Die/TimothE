#pragma once
#include "Time.h"

class Day
{
public:
	Day();
	~Day();

	void Update();

	void SetDay(bool day) { _day = day; }
	bool GetDay() { return _day; }

	void SetDayLength(float length) { _dayLength = length; }
	float GetDayLength() { return _dayLength; }

	void SetTime(float time) { _currentTime = time; }
	float GetTime() { return _currentTime; }

	void DayStart();
	void NightStart();

private:
	float _dayLength = 10.0f;
	float _currentTime;
	bool _day;
};

