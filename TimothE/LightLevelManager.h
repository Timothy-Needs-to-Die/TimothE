#pragma once
#include "glm.hpp"
#include <vector>

class TileMap;

struct LightSource
{
	int baseLightLevel;
	int fallOffRate;
	int range;
	glm::vec2 worldPos;
};

class LightLevelManager
{
private:
	std::vector<LightSource> _lightSources;
public:
	void AddLightSource(LightSource lightSource);
	void RemoveLightSource(LightSource lightSource);
	void UpdateLightMap(TileMap* tileMap);
};