#include "FarmlandManager.h"

FarmlandManager::FarmlandManager(GameObject* parent) : Component(parent)
{
	
}

bool FarmlandManager::PlaceFarmLand(glm::vec2 position)
{
	// Bool to check if a plot has been found
	bool plotAlreadyOnTile = false;


	// Make sure we dont put farmland on already existing farmland
	for (CropPlot* cropPlot : _pCropPlotObjects)
	{
		// Check if there is already plot land here
		if (GetCropPlotAtPosition(position) != nullptr)
		{
			plotAlreadyOnTile = true;
		}
	}

	glm::vec2 tilePlayerIsOnPos = SceneManager::GetCurrentScene()->GetTileMap()->GetTileAtWorldPos(0, position)->pos;
	// If there isnt any existing farmland on that plot
	if (!plotAlreadyOnTile)
	{
		// Create the new plot
		CropPlot* newCropPlot;
		// Create the name with a different gameobject name
		std::string gameObjectName = "Crop Plot " + _pCropPlotObjects.size();
		newCropPlot = new CropPlot(gameObjectName);
		// Put it in the correct place
		newCropPlot->GetTransform()->SetPosition(tilePlayerIsOnPos);
		// Add a collider for collisions
		newCropPlot->AddComponent(new BoxColliderComponent(newCropPlot));
		
		// Add the sprite  - index needs to be changed at a later date currently uses temp sprites
		SpriteComponent* sprite = newCropPlot->AddComponent(new SpriteComponent(newCropPlot));
		sprite->SetSprite(ResourceManager::GetSpriteSheet("cropspritesheet")->GetSpriteAtIndex(0));

		// Add it to the managers list
		_pCropPlotObjects.push_back(newCropPlot);
		// Add it to the game object list
		SceneManager::GetCurrentScene()->AddGameObject(newCropPlot);
		// Debug message
		std::cout << "Succesfully Created CropPlot: x:"<< tilePlayerIsOnPos.x << " y:" << tilePlayerIsOnPos.y << std::endl;
		return true;
	}
	return false;
}

void FarmlandManager::PlantSeed(glm::vec2 position, PlantResourceType cropType)
{
	// Get the crop plot from the position given
	CropPlot* cropPlot = GetCropPlotAtPosition(position);

	// If a crop plot has been found
	if (cropPlot != nullptr)
	{
		// Check if it already has a plant
		if (!cropPlot->IsOccupied())
		{
			// Create the plan
			GameObject* plantObject = new GameObject("Plant");
	
			// Make the plot its on its parent
			plantObject->SetParent(cropPlot);
			cropPlot->SetChild(plantObject);
			
			// Add Sprite component as the PlantedCrop needs it
			SpriteComponent* s = plantObject->AddComponent(new SpriteComponent(plantObject));
			PlantedCrop* crop = new PlantedCrop(cropType, 2, plantObject);
			plantObject->AddComponent(crop);
			
			// The plot now has a plant on it so it is occupied
			cropPlot->SetOccupied(true);
			
			SceneManager::GetCurrentScene()->AddGameObject(plantObject);
			// Add it to the scenes gameobjects
			// Debug message
			glm::vec2 finalPos = cropPlot->GetTransform()->GetPosition();
			std::cout << "Succesfully Planted Crop: type:" << cropType << " x:" << finalPos.x << " y:" << finalPos.y << std::endl;
		}
	}
}

void FarmlandManager::OnNewDay()
{
	for (CropPlot* plot : _pCropPlotObjects)
	{
		plot->OnNewDay();
	}
}

void FarmlandManager::OnStart()
{
}

void FarmlandManager::OnUpdate()
{
}

void FarmlandManager::OnEnd()
{
}
