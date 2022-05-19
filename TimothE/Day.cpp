#include "Day.h"
#include <iostream>
#include "Wave.h"

Day::Day() : _currentTime(0.0f), _oldDaytime(0.0f), _isDaytime(true), _dayCount(-1)
{
	
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
			StartWave();
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

void Day::StartWave()
{
	if (_pWaveController == nullptr)
	{
		return;
	}
	_pWaveController->StartWaves(_dayCount);
}
