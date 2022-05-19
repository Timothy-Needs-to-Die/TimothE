#pragma once
#include "GameObject.h"
#include "CropResourceType.h"

class CropPlot : public GameObject
{
public:
	CropPlot(std::string name = "Crop Plot", std::string tag = "UNTAGGED");
	~CropPlot();

	void OnNewDay();
	void Plant(CropResourceType type);

	bool IsOccupied() { return _isOccupied; }
	void SetOccupied(bool state) { _isOccupied = state; }
	//PlantedCrop* GetCrop() { return _crop; }

private:
	//PlantedCrop* _crop;
	bool _isOccupied;
};

