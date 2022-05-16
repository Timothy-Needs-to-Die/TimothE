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
	if (_day)
	{
		_currentTime += Time::GetDeltaTime();
	}
	if (_currentTime > _dayLength)
	{
		_day = false;
	}
}

void Day::DayStart()
{
}

void Day::NightStart()
{
}
