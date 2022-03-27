#pragma once
class Time
{
public:
	static double GetDeltaTime() { return deltaTime; };
	static void SetDeltaTime(double dt) { deltaTime = dt; };
public:
	static double deltaTime;
};
