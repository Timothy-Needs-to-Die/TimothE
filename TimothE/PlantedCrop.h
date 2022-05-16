#pragma once

#include "SpriteSheet.h"
#include "Sprite.h"
#include "CropResourceType.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

class PlantedCrop
{
public:
	PlantedCrop(CropResourceType cropType, int daysToGrow);
	~PlantedCrop();

	void AddGrowth(int growTime);
	void Harvest();

	// Get & Set Methods
	bool IsReady() { return _isReady; }
	int GetCurrentGrowTime() { return _currentGrowTime; }

private:
	bool _isReady;
	
	SpriteSheet* _cropSheet;
	SpriteComponent* _currentSprite;
	CropResourceType _type;

	int _daysToGrow;
	int _currentGrowTime;
};

