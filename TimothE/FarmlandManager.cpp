#include "FarmlandManager.h"

FarmlandManager::FarmlandManager(std::string name, std::string tag) : GameObject(name, tag)
{
	
}

void FarmlandManager::PlaceFarmLand(glm::vec2 position)
{
	
	bool plotAlreadyOnTile = false;

	// Make sure we dont put farmland on already existing farmland
	for (GameObject* cropPlotObject : _pCropPlotObjects)
	{
		// Check if there is already plot land here
		if (cropPlotObject->GetTransform()->GetPosition() == position)
		{
			plotAlreadyOnTile = true;
		}
	}

	// Get the tile position within world space
	if (!plotAlreadyOnTile)
	{
		CropPlot* newCropPlot;
		std::string gameObjectName = "Crop Plot " + _pCropPlotObjects.size();
		newCropPlot = new CropPlot(gameObjectName);
		//newCropPlot->AddComponent(new CropPlot(newCropPlot));
		newCropPlot->GetTransform()->SetPosition(position);
		newCropPlot->GetTransform()->SetScale(glm::vec2(0.25f, 0.25f));
		newCropPlot->AddComponent(new BoxColliderComponent(newCropPlot));
		
		SpriteComponent* sprite = newCropPlot->AddComponent(new SpriteComponent(newCropPlot));
		sprite->SetSprite(ResourceManager::GetSpriteSheet("testSheet")->GetSpriteAtIndex(130));

		_pCropPlotObjects.push_back(newCropPlot);
		SceneManager::GetCurrentScene()->AddGameObject(newCropPlot);
		std::cout << "Succesfully Created CropPlot: x:"<< position.x << " y:" << position.y << std::endl;
	}
}

void FarmlandManager::PlantSeed(glm::vec2 position, CropResourceType cropType)
{
	//CropPlot* cp = static_cast<CropPlot*>(cropPlot);
	CropPlot* cropPlot = GetCropPlotAtPosition(position);

	if (cropPlot != nullptr)
	{
		if (!cropPlot->IsOccupied())
		{
			// TODO here we want the user to have the seeds in their 
			// inventory to then plant the corresponding crop

			//cropPlotComponent->Plant(CropResourceType::Wheat);
			// This is just an example!

			GameObject* plantObject = new GameObject("Plant");
			//plantObject->GetTransform()->SetPosition(position);
			plantObject->GetTransform()->SetScale(glm::vec2(0.25f, 0.25f));
			plantObject->SetParent(cropPlot);
			SpriteComponent* s = plantObject->AddComponent(new SpriteComponent(plantObject));
			s->SetSprite(ResourceManager::GetSpriteSheet("testSheet")->GetSpriteAtIndex(24));
			cropPlot->SetOccupied(true);

			SceneManager::GetCurrentScene()->AddGameObject(plantObject);
			std::cout << "Succesfully Planted Crop: type:" << cropType << " x:" << position.x << " y:" << position.y << std::endl;

		}
	}
}
