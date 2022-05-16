#include "CropPlot.h"

CropPlot::CropPlot(GameObject* parent) : Component(parent)
{
	_crop = nullptr;
	_isOccupied = false;
}

CropPlot::~CropPlot()
{
	
}

void CropPlot::OnNewDay()
{	
	// If theres a crop apply age to the crop
	if (_isOccupied)
	{
		_crop->AddGrowth(1);
	}
}

void CropPlot::Plant(CropResourceType type)
{
	// If there isnt currently a crop
	if (!_isOccupied)
	{
		// Plant one
		_isOccupied = true;
		_crop = new PlantedCrop(type, 3);
	}
}

void CropPlot::OnStart()
{
}

void CropPlot::OnUpdate()
{
}

void CropPlot::OnEnd()
{
}
