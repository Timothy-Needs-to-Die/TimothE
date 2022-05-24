#pragma once
#include "glm.hpp"
#include <vector>

class TileMap;

struct LightSource
{
	LightSource() : baseLightLevel(5), fallOffRate(1.0f), range(10), worldPos(glm::vec2(0.0f, 0.0f))
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
	LightLevelManager(TileMap* tileMap);
public:
	void AddLightSource(LightSource lightSource);
	void RemoveLightSource(LightSource lightSource);
	void UpdateLightMap();
	void SetWorldLightLevel(int value);
	
public:
	std::vector<LightSource> _lightSources;
	int _worldLightLevel;
	TileMap* _pTileMap;
};