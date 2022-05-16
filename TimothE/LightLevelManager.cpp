#include "LightLevelManager.h"
#include "TileMap.h"

void LightLevelManager::UpdateLightMap(TileMap& tileMap)
{
	/*for (TileData obj : tileMap.GetTiles())
	{
		obj.lightLevel = 0;
	}*/

	float xMin, xMax;
	float yMin, yMax;
	float tileXSize = tileMap.GetTileSize().x;
	float tileYSize = tileMap.GetTileSize().y;

	for (LightSource source : _lightSources)
	{
		//needs to loop through layers
		xMin = tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x - (source.range * tileMap.GetTileSize().x), source.worldPos.y))->colXPos;
		xMax = tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x + (source.range * tileMap.GetTileSize().x), source.worldPos.y))->colXPos;
		yMin = tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x, source.worldPos.y - (source.range * tileMap.GetTileSize().y)))->colYPos;
		yMax = tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x, source.worldPos.y + (source.range * tileMap.GetTileSize().y)))->colYPos;

		for (float y = yMin; y <= yMax; tileYSize++)
		{
			for (float x = xMin; x <= xMax; tileXSize++)
			{
				TileData* tile;  tileMap.GetTileAtWorldPos(0, glm::vec2(x, y));

				//get affective light value
				//get final light value and apply to tile
			}
		}
	}
}

void LightLevelManager::RemoveLightSource(LightSource lightSource)
{
	//_lightSources.erase(std::find(_lightSources.begin(), _lightSources.end(), lightSource));
}
