#pragma once

#include "GameObject.h"
#include "PlantResourceType.h"
#include "SpriteComponent.h"

class PlantedCrop : public Component
{
public:
	PlantedCrop(PlantResourceType cropType, int daysToGrow, int startSpriteIndex, GameObject* parent);
	~PlantedCrop();

	void AddGrowth(int growTime = 1);
	bool Harvest();

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;
	
	// Get & Set Methods
	bool IsHarvestable() { return _isHarvestable; }
	int GetCurrentGrowTime() { return _currentGrowTime; }
	PlantResourceType GetCrop() { return _type; }

private:
	bool _isHarvestable;
	
	SpriteComponent* _pSpriteComponent = nullptr;
	PlantResourceType _type;

	int _daysToGrow;
	int _currentGrowTime;
	int _spriteIndex;

protected:
};

