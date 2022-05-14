#include "LightLevelManager.h"
#include "TileMap.h"

void LightLevelManager::UpdateLightMap(TileMap& tileMap)
{
	/*for (TileData obj : tileMap.GetTiles())
	{
		obj.lightLevel = 0;
	}*/

	std::vector<float> xMin;
	std::vector<float> xMax;
	std::vector<float> yMin;
	std::vector<float> yMax;

	for (LightSource source : _lightSources)
	{
		//needs to loop through layers
		xMin.push_back(tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x - (source.range * tileMap.GetTileSize().x), source.worldPos.y))->colXPos);
		xMax.push_back(tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x + (source.range * tileMap.GetTileSize().x), source.worldPos.y))->colXPos);
		yMin.push_back(tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x, source.worldPos.y - (source.range * tileMap.GetTileSize().y)))->colYPos);
		yMax.push_back(tileMap.GetTileAtWorldPos(0, glm::vec2(source.worldPos.x, source.worldPos.y + (source.range * tileMap.GetTileSize().y)))->colYPos);
	}

	xMin.clear();
	xMax.clear();
	yMin.clear();
	yMax.clear();
}

void LightLevelManager::RemoveLightSource(LightSource lightSource)
{
	//_lightSources.erase(std::find(_lightSources.begin(), _lightSources.end(), lightSource));
}
