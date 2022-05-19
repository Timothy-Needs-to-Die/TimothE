#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Scene.h"

#include "CropPlot.h"
#include "CropResourceType.h"

class FarmlandManager : public GameObject
{
public:
	FarmlandManager(Scene* currentScene, std::string name = "Farmland", std::string tag = "UNTAGGED");

	void PlaceFarmLand(glm::vec2 position);
	void PlantSeed(glm::vec2 position, CropResourceType cropType);

	CropPlot* GetCropPlotAtPosition(glm::vec2 pos)
	{
		std::cout << "Searching for CropPlot at: x:" << pos.x << " y:" << pos.y;

		for (CropPlot* go : _pCropPlotObjects)
		{
			if (go->GetTransform()->GetPosition() == pos)
			{
				std::cout << " Success!" << std::endl;
				return go;
			}
		}
		std::cout << " Fail!" << std::endl;
		return nullptr;
	}

private:

	Scene* _pCurrentScene;

	vector<CropPlot*> _pCropPlotObjects;
	//vector<SpriteComponent*> _pCropPlotSpriteComponents;
	//SpriteComponent* _pCropPlotBaseSpriteComponent = nullptr;
	//GameObject* _pCropPlotBaseObject = nullptr;

protected:
	//virtual void UniqueLogic() override;
};

