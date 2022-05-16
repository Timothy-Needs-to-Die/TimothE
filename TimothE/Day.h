#pragma once
#include "Time.h"

class Day
{
public:
	Day();
	~Day();

	void Update();

	void SetDay(bool day) { _isDay = day; }

private:
	const float _dayLength = 10.0f;
	float _currentTime;
	bool _isDay;
};

