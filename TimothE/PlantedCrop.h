#pragma once

#include "GameObject.h"
#include "PlantResourceType.h"
#include "SpriteComponent.h"

class PlantedCrop : public Component
{
public:
	PlantedCrop(PlantResourceType cropType, int daysToGrow, GameObject* parent);
	~PlantedCrop();

	void AddGrowth(int growTime);
	void Harvest();

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	
	// Get & Set Methods
	bool IsHarvestable() { return _isHarvestable; }
	int GetCurrentGrowTime() { return _currentGrowTime; }

private:
	bool _isHarvestable;
	
	SpriteComponent* _pSpriteComponent = nullptr;
	PlantResourceType _type;

	int _daysToGrow;
	int _currentGrowTime;

protected:
};

