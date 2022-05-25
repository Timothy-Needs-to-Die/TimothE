#pragma once
#include "GameObject.h"
#include "PlantedCrop.h"
#include "PlantResourceType.h"
#include "PlayerResourceManager.h"

class CropPlot : public GameObject
{
public:
	/// <summary>
	/// Constructor - Sets up gameobject class
	/// </summary>
	/// <param name="name"> GameObject name </param>
	/// <param name="tag"> GameObject tag </param>
	CropPlot(std::string name = "Crop Plot", std::string tag = "UNTAGGED");
	~CropPlot();

	void OnNewDay();
	void Harvest();

	bool IsOccupied() { return _isOccupied; }
	void SetOccupied(bool state) { _isOccupied = state; }

private:
	bool _isOccupied;
};

