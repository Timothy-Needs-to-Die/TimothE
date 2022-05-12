#include "LightLevelManager.h"
#include "TileMap.h"

void LightLevelManager::UpdateLightMap(TileMap& tileMap)
{
	/*for (TileData obj : tileMap.GetTiles())
	{
		obj.lightLevel = 0;
	}*/

	for (LightSource source : _lightSources)
	{
		//needs to loop through layers
		//float xMin = source.worldPos.x - source.range;
	}
}

void LightLevelManager::RemoveLightSource(LightSource lightSource)
{
	_lightSources.erase(std::find(_lightSources.begin(), _lightSources.end(), lightSource));
}
