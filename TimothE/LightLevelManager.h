#pragma once
#include "glm.hpp"
#include <vector>

class TileMap;

struct LightSource
{
	LightSource() : baseLightLevel(6), fallOffRate(1.0f), range(10), worldPos(glm::vec2(3.0f, 3.0f))
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

public:
	//getters
	int GetWorldLightLevel() { return _worldLightLevel; }
	int GetMinTileLightLevel() { return _minLightLevel; }
	int GetMaxTileLightLevel() { return _maxLightLevel; }

	//setters
	
	//set the base light level for all the tiles in the tile map.
	void SetWorldLightLevel(int level);

	//Set the minimum light level a tile can have.
	void SetMinLightLevel(int level)
	{
		_minLightLevel = level;
		UpdateLightMap();
	}

	//Set the maximum light level a tile can have.
	void SetMaxLightLevel(int level)
	{
		_maxLightLevel = level;
		UpdateLightMap();
	}
	
private:
	std::vector<LightSource> _lightSources;
	int _worldLightLevel;
	int _minLightLevel;
	int _maxLightLevel;
	TileMap* _pTileMap;
};