#include "CropPlot.h"

CropPlot::CropPlot(std::string name, std::string tag) : GameObject(name, tag)
{
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
		GetChild()->GetComponent<PlantedCrop>()->AddGrowth(1);
	}
}

void CropPlot::Harvest()
{
	if (_isOccupied)
	{
		PlantedCrop* plantedCrop = GetChild()->GetComponent<PlantedCrop>();

		if (plantedCrop->Harvest())
		{
			PlayerResourceManager::GetPlantResource(plantedCrop->GetCrop())->GainResource(1);

			// Just destroy the object for now
			GetChild()->SetToBeDestroyed(true);
			_isOccupied = false;
		}
	}
}

