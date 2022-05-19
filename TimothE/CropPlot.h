#pragma once
#include "PlantedCrop.h"

class CropPlot : public Component
{
public:
	CropPlot(GameObject* parent);
	~CropPlot();

	void OnNewDay();
	void Plant(CropResourceType type);

	bool IsOccupied() { return _isOccupied; }
	//PlantedCrop* GetCrop() { return _crop; }

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

private:
	//PlantedCrop* _crop;
	bool _isOccupied;
};

