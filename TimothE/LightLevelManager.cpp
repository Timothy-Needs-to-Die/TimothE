#include "LightLevelManager.h"
#include "TileMap.h"

LightLevelManager::LightLevelManager(TileMap* tileMap) : _pTileMap(tileMap)
{
	SetWorldLightLevel(0);
}

void LightLevelManager::UpdateLightMap()
{
	_pTileMap->SetAllTilesLightLevel(_worldLightLevel);

	if (_lightSources.size() > 0)
	{

		float xMin, xMax;
		float yMin, yMax;
		float tileSize = 0.25f;

		for (auto const& source : _lightSources)
		{
			if (source->isEnabled)
			{
				//No need to get different x and y min/max values as they are the same as across all layers
				xMin = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x - (source->range * tileSize), source->worldPos.y))->pos.x;
				xMax = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x + (source->range * tileSize), source->worldPos.y))->pos.x;
				yMin = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x, source->worldPos.y - (source->range * tileSize)))->pos.y;
				yMax = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x, source->worldPos.y + (source->range * tileSize)))->pos.y;

				for (int i = 0; i < 6; i++)
				{
					for (float y = yMin; y <= yMax; y += tileSize)
					{
						for (float x = xMin; x <= xMax; x += tileSize)
						{
							TileData* tile = _pTileMap->GetTileAtWorldPos(i, glm::vec2(x, y));

							//get affective light value = baselight - (falloff * distance of tiles between source and tile rounded)
							int affectiveValue = source->baseLightLevel - (source->fallOffRate * (int)round(glm::distance(glm::vec2(x, y), source->worldPos) / tileSize));
							if (affectiveValue < 0) affectiveValue = 0;

							if ((tile->lightLevel + affectiveValue) < _worldLightLevel)
							{
								tile->lightLevel = _worldLightLevel;
								continue;
							}
							else if ((tile->lightLevel + affectiveValue) > _maxLightLevel)
							{
								tile->lightLevel = _maxLightLevel;
								continue;
							}

							//get final light value and apply to tile
							tile->lightLevel += affectiveValue;
						}
					}
				}
			}
		}
	}
}

void LightLevelManager::SetWorldLightLevel(int value)
{
	//set light level variable
	_worldLightLevel = value;

	_pTileMap->SetAllTilesLightLevel(value);

	UpdateLightMap();
}

void LightLevelManager::AddLightSource(LightSource* lightSource)
{
	_lightSources.push_back(lightSource);
	UpdateLightMap();
}

void LightLevelManager::RemoveLightSource(LightSource* lightSource)
{
	std::vector<LightSource*>::iterator it;
	it = std::find(_lightSources.begin(), _lightSources.end(), lightSource);

	if (it != _lightSources.end()) {
		_lightSources.erase(it);
	}
	UpdateLightMap();
	//_lightSources.erase(std::find(_lightSources.begin(), _lightSources.end(), lightSource));
}
