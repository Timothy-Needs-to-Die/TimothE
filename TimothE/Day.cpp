#include "Day.h"
#include <iostream>

Day::Day()
{
	_currentTime = 0.0f;
	_day = true;
}

Day::~Day()
{
}

void Day::Update()
{
	_oldDay = _day;
	if (_day)
	{
		_currentTime += Time::GetDeltaTime();
	}
	if (_currentTime > _dayLength)
	{
		_day = false;
	}
}

bool Day::NightStart()
{
	if (_oldDay && !_day)
	{
		return true;
	}
	return false;
}
