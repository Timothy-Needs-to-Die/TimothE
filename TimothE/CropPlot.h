#pragma once
#include "GameObject.h"
#include "PlantResourceType.h"

class CropPlot : public GameObject
{
public:
	CropPlot(std::string name = "Crop Plot", std::string tag = "UNTAGGED");
	~CropPlot();

	void OnNewDay();
	void Plant(PlantResourceType type);

	bool IsOccupied() { return _isOccupied; }
	void SetOccupied(bool state) { _isOccupied = state; }
	//PlantedCrop* GetCrop() { return _crop; }

private:
	//PlantedCrop* _crop;
	bool _isOccupied;
};

