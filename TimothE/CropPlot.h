#pragma once
#include "PlantedCrop.h"

class CropPlot : public Component
{
public:
	CropPlot();
	~CropPlot();

	void OnNewDay();
	void Plant(CropResourceType type);

	bool IsOccupied() { return _isOccupied; }
	PlantedCrop* GetCrop() { return _crop; }

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

private:
	glm::vec2 _TilePos;

	PlantedCrop* _crop;
	bool _isOccupied;
};

