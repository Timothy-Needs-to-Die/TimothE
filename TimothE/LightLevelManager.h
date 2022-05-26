#pragma once
#include "glm.hpp"
#include <vector>

class TileMap;

struct LightSource
{
	LightSource() : baseLightLevel(6), fallOffRate(1.0f), range(10), worldPos(glm::vec2(0.0f, 0.0f))
	{
		
	}

	int baseLightLevel;
	int fallOffRate;
	int range;
	glm::vec2 worldPos;
	bool isEnabled = true;
};

class LightLevelManager
{
public:
	LightLevelManager(TileMap* tileMap);
public:
	void AddLightSource(LightSource* lightSource);
	void RemoveLightSource(LightSource* lightSource);
	void UpdateLightMap();

public:
	//getters
	int GetWorldLightLevel() { return _worldLightLevel; }
	int GetMinTileLightLevel() { return _minLightLevel; }
	int GetMaxTileLightLevel() { return _maxLightLevel; }
	bool GetSourceEnabledState(int index) { return _lightSources[index]->isEnabled; }

	//setters
	
	//Set the base light level for all the tiles in the tile map.
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

	//Set whether light source is enabled or disabled.
	void SetSourceEnabledState(int index, bool state) 
	{ 
		if (index <= _lightSources.size() - 1)
		{
			if (_lightSources[index]->isEnabled != state)
			{
				_lightSources[index]->isEnabled = state;

				SetWorldLightLevel(_worldLightLevel);
				UpdateLightMap();
			}
		}
	}
	
private:
	std::vector<LightSource*> _lightSources;
	int _worldLightLevel;
	int _minLightLevel;
	int _maxLightLevel;
	TileMap* _pTileMap;
};