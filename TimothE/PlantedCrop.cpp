#include "PlantedCrop.h"

/*
	Planted Crop
	Stores its texture to be rendered above of the farm land
	
	Need information as to how many stages of growth there is 
	for example wheat may take 10 days but only have 5 textures = 2 days per texture 
	But:
	potatoes may have 4 textures and take 4 days = 1 day per texture

*/

PlantedCrop::PlantedCrop(PlantResourceType cropType, int daysToGrow, GameObject* parent) : Component(parent)
{
	/*int sheetX = 6, sheetY = 11;
	SpriteSheet* sheet = ResourceManager::GetSpriteSheet("testSheet");
	_currentSprite->SetSprite(sheet->GetSpriteAtIndex(sheet->GetSheetWidth() * sheetX + sheetY));*/

	// Set the sprite
	_pSpriteComponent = parent->GetComponent<SpriteComponent>();
	_pSpriteComponent->SetSprite(ResourceManager::GetSpriteSheet("spritesheet")->GetSpriteAtIndex(24));

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

void PlantedCrop::OnStart()
{
}

void PlantedCrop::OnUpdate()
{
}

void PlantedCrop::OnEnd()
{
}

