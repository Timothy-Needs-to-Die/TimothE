#include "Day.h"
#include <iostream>
#include "Wave.h"
#include "CSVReader.h"

Day::Day() : _currentTime(0.0f), _oldDaytime(0.0f), _isDaytime(true), _dayCount(0)
{
	UpdateDayLength();
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
			UpdateDayLength();
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

void Day::UpdateDayLength()
{
	std::vector<std::vector<std::string>> dayConfig = CSVReader::RequestDataFromFile("Resources/Data/DayConfig.csv");
	if (dayConfig.size() == 0)
	{
		return;
	}

	bool foundDay = false;
	for (int i = 0; i < dayConfig.size(); i++)
	{
		if (std::stoi(dayConfig[i][0]) == _dayCount)
		{
			foundDay = true;
			_dayLength = std::stoi(dayConfig[i][1]);
			break;
		}
	}
	if (!foundDay)
	{
		// if greater than the final day in config, set to the final day
		int i = dayConfig.size() - 1;
		_dayLength = std::stoi(dayConfig[i][1]);
	}
}

void Day::StartWave()
{
	//if (_pWaveController == nullptr)
	//{
	//	return;
	//}
	//_pWaveController->StartWaves(_dayCount);
}
