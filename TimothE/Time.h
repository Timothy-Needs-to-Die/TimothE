#pragma once

class Time
{
public:
	//Update time variables
	static void Update(double dt, double t)
	{
		_deltaTime = dt;
		_time = t;
	}

	//Get the interval in seconds from the last frame to the current one
	static double GetDeltaTime() { return _deltaTime; };

	//Get the interval in seconds from when the application started
	static double GetTime() { return _time; };
private:
	//interval in seconds from the last frame to the current one
	static double _deltaTime;
	//interval in seconds from when the application started
	static double _time;
};