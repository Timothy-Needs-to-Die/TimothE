#pragma once

class Time
{
public:
	//Update time variables
	static void Update(float dt, float t)
	{
		_deltaTime = dt;
		_time = t;
	}

	//Get the interval in seconds from the last frame to the current one
	static float GetDeltaTime() { return _deltaTime; };

	//Get the interval in seconds from when the application started
	static float GetTime() { return _time; };
private:
	//interval in seconds from the last frame to the current one
	static float _deltaTime;
	//interval in seconds from when the application started
	static float _time;
};