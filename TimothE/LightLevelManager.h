#pragma once
#include "glm.hpp"
#include <vector>

class TileMap;

struct LightSource
{
	LightSource() : baseLightLevel(7), fallOffRate(1), range(10), worldPos(glm::vec2(0.0f, 0.0f))
	{

	}

	int baseLightLevel;
	int fallOffRate;
	int range;
	glm::vec2 worldPos;
};

class LightLevelManager
{
public:
	std::vector<LightSource> _lightSources;
public:
	void AddLightSource(LightSource lightSource);
	void RemoveLightSource(LightSource lightSource);
	void UpdateLightMap(TileMap* tileMap);
};