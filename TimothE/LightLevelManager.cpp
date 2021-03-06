#include "pch.h"
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
		float tileSize = _pTileMap->GetTileSize();

		for (auto const& source : _lightSources)
		{
			if (!source->isEnabled) continue;

			//No need to get different x and y min/max values as they are the same as across all layers
			xMin = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x - (source->range * tileSize), source->worldPos.y))->pos.x;
			xMax = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x + (source->range * tileSize), source->worldPos.y))->pos.x;
			yMin = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x, source->worldPos.y - (source->range * tileSize)))->pos.y;
			yMax = _pTileMap->GetTileAtWorldPos(0, glm::vec2(source->worldPos.x, source->worldPos.y + (source->range * tileSize)))->pos.y;

			for (float y = yMin; y <= yMax; y += tileSize)
			{
				for (float x = xMin; x <= xMax; x += tileSize)
				{
					int index = _pTileMap->GetTileIndexFromPosition({ x,y });

					TileData* tile = _pTileMap->GetTileAtWorldPos(0, glm::vec2(x, y));

					int level = _pTileMap->GetLightLevelAtPosition({ x,y });
					
					int affectiveValue = source->baseLightLevel - (source->fallOffRate * (int)round(glm::distance(glm::vec2(x, y), source->worldPos) / tileSize));
					if (affectiveValue < 0) affectiveValue = 0;

					if ((level + affectiveValue) < _worldLightLevel)
					{
						_pTileMap->UpdateLightLevelAtPosition({ x,y }, _worldLightLevel);
						continue;
					}
					else if ((level + affectiveValue) > _maxLightLevel)
					{
						_pTileMap->UpdateLightLevelAtPosition({ x,y }, _maxLightLevel);
						continue;
					}

					//get final light value and apply to tile
					level += affectiveValue;

					_pTileMap->UpdateLightLevelAtPosition({ x,y }, level);
				}
			}
		}

		_pTileMap->UpdateRenderInfo();
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

	TIM_LOG_LOG("Placing tile at position: " << lightSource->worldPos.x << ", " << lightSource->worldPos.y);

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
