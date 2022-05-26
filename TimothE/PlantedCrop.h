#pragma once

#include "GameObject.h"
#include "PlantResourceType.h"

class PlantedCrop : public GameObject
{
public:
	PlantedCrop(PlantResourceType cropType, int daysToGrow, std::string name = "Planted Crop", std::string tag = "UNTAGGED");
	~PlantedCrop();

	void AddGrowth(int growTime);
	void Harvest();

	// Get & Set Methods
	bool IsReady() { return _isReady; }
	int GetCurrentGrowTime() { return _currentGrowTime; }

private:
	bool _isReady;
	
	class SpriteSheet* _cropSheet;
	class SpriteComponent* _currentSprite;
	PlantResourceType _type;

	int _daysToGrow;
	int _currentGrowTime;

protected:
};

