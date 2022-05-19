#include "PlantedCrop.h"

/*
	Planted Crop
	Stores its texture to be rendered above of the farm land
	
	Need information as to how many stages of growth there is 
	for example wheat may take 10 days but only have 5 textures = 2 days per texture 
	But:
	potatoes may have 4 textures and take 4 days = 1 day per texture

*/

PlantedCrop::PlantedCrop(PlantResourceType cropType, int daysToGrow, std::string name, std::string tag) : GameObject(name, tag)
{
	/*int sheetX = 6, sheetY = 11;
	SpriteSheet* sheet = ResourceManager::GetSpriteSheet("testSheet");
	_currentSprite->SetSprite(sheet->GetSpriteAtIndex(sheet->GetSheetWidth() * sheetX + sheetY));*/

	_type = cropType;
	_daysToGrow = daysToGrow;
	_currentGrowTime = 0;
}

PlantedCrop::~PlantedCrop()
{
}

void PlantedCrop::AddGrowth(int growTime)
{
	_currentGrowTime += growTime;

	if (_currentGrowTime > _daysToGrow)
	{
		_isReady = true;
	}	
}

void PlantedCrop::Harvest()
{

}

