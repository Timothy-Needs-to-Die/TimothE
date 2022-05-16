#include "Day.h"
#include <iostream>

Day::Day()
{
	_currentTime = 0.0f;
	_isDay = true;
}

Day::~Day()
{
}

void Day::Update()
{
	if (_isDay)
	{
		_currentTime += Time::GetDeltaTime();
	}
	if (_currentTime > _dayLength)
	{
		_isDay = false;
	}
}
