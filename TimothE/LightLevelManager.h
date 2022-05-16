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
public:
	void AddLightSource(LightSource lightSource) { _lightSources.push_back(lightSource); };
	void RemoveLightSource(LightSource lightSource);
	void UpdateLightMap(TileMap* tileMap);

private:
	std::vector<LightSource> _lightSources;
};