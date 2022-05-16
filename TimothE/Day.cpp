#include "Day.h"
#include <iostream>

Day::Day()
{
	_currentTime = 0.0f;
	_isDaytime = true;
	_dayCount = -1;
}

Day::~Day()
{
}

void Day::Update()
{
	_oldDaytime = _isDaytime;
	if (_isDaytime)
	{
		_currentTime += Time::GetDeltaTime();

		if (_currentTime > _dayLength)
		{
			_isDaytime = false;
			_dayCount++;
		}
	}
}

bool Day::NightStart()
{
	if (_oldDaytime && !_isDaytime)
	{
		return true;
	}
	return false;
}
