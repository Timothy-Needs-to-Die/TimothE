#include "FarmlandManager.h"

FarmlandManager::FarmlandManager(std::string name, std::string tag) : GameObject(name, tag)
{
	
}

void FarmlandManager::PlaceFarmLand(glm::vec2 position)
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

	glm::vec2 tilePlayerIsOnPos = { SceneManager::GetCurrentScene()->GetTileMap()->GetTileAtWorldPos(0, position)->colXPos, SceneManager::GetCurrentScene()->GetTileMap()->GetTileAtWorldPos(0, position)->colYPos };
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
		newCropPlot->GetTransform()->SetScale(glm::vec2(0.25f, 0.25f));
		// Add a collider for collisions
		newCropPlot->AddComponent(new BoxColliderComponent(newCropPlot));
		
		// Add the sprite  - index needs to be changed at a later date currently uses temp sprites
		SpriteComponent* sprite = newCropPlot->AddComponent(new SpriteComponent(newCropPlot));
		sprite->SetSprite(ResourceManager::GetSpriteSheet("testSheet")->GetSpriteAtIndex(130));

		// Add it to the managers list
		_pCropPlotObjects.push_back(newCropPlot);
		// Add it to the game object list
		SceneManager::GetCurrentScene()->AddGameObject(newCropPlot);
		// Debug message
		std::cout << "Succesfully Created CropPlot: x:"<< tilePlayerIsOnPos.x << " y:" << tilePlayerIsOnPos.y << std::endl;
	}
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
			// Set its correct W and H
			plantObject->GetTransform()->SetScale(glm::vec2(0.25f, 0.25f));
			// Make the plot its on its parent
			plantObject->SetParent(cropPlot);

			// Set the sprite
			SpriteComponent* s = plantObject->AddComponent(new SpriteComponent(plantObject));
			s->SetSprite(ResourceManager::GetSpriteSheet("testSheet")->GetSpriteAtIndex(24));
			// The plot now has a plant on it so it is occupied
			cropPlot->SetOccupied(true);

			// Add it to the scenes gameobjects
			SceneManager::GetCurrentScene()->AddGameObject(plantObject);
			// Debug message
			glm::vec2 finalPos = cropPlot->GetTransform()->GetPosition();
			std::cout << "Succesfully Planted Crop: type:" << cropType << " x:" << finalPos.x << " y:" << finalPos.y << std::endl;
		}
	}
}
