#include "LightLevelManager.h"
#include "TileMap.h"

void LightLevelManager::UpdateLightMap(TileMap* tileMap)
{
	if (_lightSources.size() > 0)
	{
		float xMin, xMax;
		float yMin, yMax;
		float tileSize = 0.25f;

		for (auto const& source : _lightSources)
		{
			//tileMap->GetTileIndexFromPosition

			//needs to loop through layers
			//xMin = tileMap->GetTileAtWorldPos(0, glm::vec2(source.worldPos.x - (source.range * tileSize), source.worldPos.y))->pos.x;
			//xMax = tileMap->GetTileAtWorldPos(0, glm::vec2(source.worldPos.x + (source.range * tileSize), source.worldPos.y))->pos.x;
			//yMin = tileMap->GetTileAtWorldPos(0, glm::vec2(source.worldPos.x, source.worldPos.y - (source.range * tileSize)))->pos.y;
			//yMax = tileMap->GetTileAtWorldPos(0, glm::vec2(source.worldPos.x, source.worldPos.y + (source.range * tileSize)))->pos.y;

			xMin = tileMap->GetTileAtWorldPos(0, glm::vec2(2.0f, 2.0f))->pos.x - 30.0f;
			xMax = tileMap->GetTileAtWorldPos(0, glm::vec2(2.0f, 2.0f))->pos.x + 30.0f;
			yMin = tileMap->GetTileAtWorldPos(0, glm::vec2(2.0f, 2.0f))->pos.y - 30.0f;
			yMax = tileMap->GetTileAtWorldPos(0, glm::vec2(2.0f, 2.0f))->pos.y + 30.0f;

			for (float y = yMin; y <= yMax; y += tileSize)
			{
				for (float x = xMin; x <= xMax; x += tileSize)
				{
					TileData* tile = tileMap->GetTileAtWorldPos(0, glm::vec2(x, y));

					//get affective light value = baselight - (falloff * distance of tiles between source and tile rounded)
					int affectiveValue = source.baseLightLevel - (source.fallOffRate * (int)round(glm::distance(glm::vec2(x, y), source.worldPos) / tileSize));

					//get final light value and apply to tile
					tile->lightLevel += affectiveValue;
				}
			}
		}
	}
}

void LightLevelManager::AddLightSource(LightSource lightSource)
{
	_lightSources.push_back(lightSource);
}

void LightLevelManager::RemoveLightSource(LightSource lightSource)
{
	//_lightSources.erase(std::find(_lightSources.begin(), _lightSources.end(), lightSource));
}
