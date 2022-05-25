#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "SceneManager.h"

#include "CropPlot.h"
#include "PlantResourceType.h"
#include "PlantedCrop.h"

class FarmlandManager : public Component
{
public:

	/// <summary>
	/// Constructor - Sets up the gameobject constructor using set params
	/// </summary>
	/// <param> GameObject - parent the component is being attached to </param>
	FarmlandManager(GameObject* parent);

	/// <summary>
	/// Place a "CropPlot" at the desired location
	/// Checks if the plot has already got a "CropPlot" on it
	/// </summary>
	/// <param name="position"> The Position we want to place the CropPlot</param>
	void PlaceFarmLand(glm::vec2 position);

	/// <summary>
	/// Plant the seed at the desired location
	/// </summary>
	/// <param name="position"> The position of the plot we wish to plant a seed on</param>
	/// <param name="cropType"> The type of crop we wish to plant</param>
	void PlantSeed(glm::vec2 position, PlantResourceType cropType);

	void OnNewDay();

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnEnd() override;

	/// <summary>
	/// Function to get a "CropPlot" at a given position - Uses true positions (bottom left corner)
	/// </summary>
	/// <param name="pos"> Desired position </param>
	/// <returns> Returns the cropplot if it exists, if not returns nullptr </returns>
	CropPlot* GetCropPlotAtTruePosition(glm::vec2 pos)
	{
		// Debug message
		//std::cout << "Searching for CropPlot at: x:" << pos.x << " y:" << pos.y;

		// Loop through all the existing CropPlots
		for (CropPlot* go : _pCropPlotObjects)
		{
			// check the transforms
			if (go->GetTransform()->GetPosition() == pos)
			{
				// Debug message
				//std::cout << " Success!" << std::endl;
				return go;
			}
		}
		// Debug message
		//std::cout << " Fail!" << std::endl;
		return nullptr;
	}

	CropPlot* GetCropPlotAtPosition(glm::vec2 pos)
	{
		//std::cout << "Searching for CropPlot at: x:" << pos.x << " y:" << pos.y;
		for (CropPlot* go : _pCropPlotObjects)
		{
			if(Physics::Intersects(go->GetComponent<BoxColliderComponent>(), pos))
			{
				//std::cout << "Success!" << std::endl;
				return go;
			}
		}
		//std::cout << "Fail!" << std::endl;
		return nullptr;
	}

private:

	vector<CropPlot*> _pCropPlotObjects;

protected:
	
};

