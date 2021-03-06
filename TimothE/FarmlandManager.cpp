#include "pch.h"
#include "FarmlandManager.h"

//std::vector<CropConfig> FarmlandManager::_pCropData = std::vector<CropConfig>();

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

	// Farm Bounds
	Rect* r1 = new Rect(4, 1.5, 6, 5);

	if (tilePlayerIsOnPos.x > r1->xPos && tilePlayerIsOnPos.x < r1->xPos + r1->width && tilePlayerIsOnPos.y > r1->yPos && tilePlayerIsOnPos.y < r1->yPos + r1->height) 
	{
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
			SpriteComponent* sprite = newCropPlot->AddComponent(new SpriteComponent(newCropPlot, 100));
			sprite->SetSprite(ResourceManager::GetSpriteSheet("cropspritesheet")->GetSpriteAtIndex(0));

			// Add it to the managers list
			_pCropPlotObjects.push_back(newCropPlot);
			// Add it to the game object list
			SceneManager::GetCurrentScene()->AddGameObject(newCropPlot);
			// Debug message
			std::cout << "Succesfully Created CropPlot: x:" << tilePlayerIsOnPos.x << " y:" << tilePlayerIsOnPos.y << std::endl;
			return true;
		}
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
			// Get our CropsConfig
			CropConfig cropConfig;
			for (CropConfig c : _pCropData)
			{
				if (c.type == cropType)
				{
					cropConfig = c;
				}
			}

			if (PlayerResourceManager::GetPlantResource(cropType)->GetAmount() > 0)
			{
				// Create the plan
				GameObject* plantObject = new GameObject("Plant");

				// Make the plot its on its parent
				plantObject->SetParent(cropPlot);
				//cropPlot->SetChild(plantObject);

				// Add Sprite component as the PlantedCrop needs it
				SpriteComponent* s = plantObject->AddComponent(new SpriteComponent(plantObject, 110));

				PlantedCrop* crop = new PlantedCrop(cropConfig.type, cropConfig.growthRate, cropConfig.startSpriteIndex, plantObject);
				plantObject->AddComponent(crop);

				// The plot now has a plant on it so it is occupied
				cropPlot->SetOccupied(true);

				SceneManager::GetCurrentScene()->AddGameObject(plantObject);

				PlayerResourceManager::GetPlantResource(cropType)->SpendResource(1);
				// Add it to the scenes gameobjects
				// Debug message
				glm::vec2 finalPos = cropPlot->GetTransform()->GetPosition();
				std::cout << "Succesfully Planted Crop: type:" << cropType << " x:" << finalPos.x << " y:" << finalPos.y << std::endl;
			}
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

void FarmlandManager::LoadInCropData()
{
	std::vector<std::vector<std::string>> loadedData = CSVReader::RequestDataFromFile("Resources/Data/SeedsConfig.csv");
	for (int i = 0; i < loadedData.size(); i++)
	{
		CropConfig newConfig;

		newConfig.name = loadedData[i][1];
		newConfig.sellPrice = std::stoi(loadedData[i][2]);
		newConfig.description = loadedData[i][3];
		newConfig.growthRate = std::stoi(loadedData[i][4]);
		newConfig.type = (PlantResourceType)std::stoi(loadedData[i][5]);
		newConfig.quality = std::stoi(loadedData[i][6]);
		newConfig.startSpriteIndex = std::stoi(loadedData[i][7]);
		newConfig.yield = std::stoi(loadedData[i][8]);
		newConfig.produceType = (PlantResourceType)std::stoi(loadedData[i][9]);
		newConfig.icon = nullptr;

		_pCropData.emplace_back(newConfig);
	}
}

void FarmlandManager::HarvestPlot(CropPlot* plot)
{
	// If the plot exists
	if (plot != nullptr)
	{
		//PlantedCrop* plantedCrop = plot->GetChild()->GetComponent<PlantedCrop>();
		//// Get our CropsConfig
		//CropConfig cropConfig;
		//for (CropConfig c : _pCropData)
		//{
		//	// If the data is that of the current crop being harvested
		//	if (c.type == plantedCrop->GetCrop())
		//	{
		//		cropConfig = c;
		//	}
		//}
		//
		//// If we can succesfully harvest the crop
		//if (plantedCrop->Harvest())
		//{
		//	// Add the resources to the players inventory
		//	PlayerResourceManager::GetPlantResource(cropConfig.produceType)->GainResource(cropConfig.yield);
		//	// For now just destroy the game object - Future work: Object Pooling
		//	plot->SetOccupied(false);
		//	plot->GetChild()->SetToBeDestroyed(true);
		//}
	}
	
}

void FarmlandManager::RemoveCropPlot(CropPlot* plot)
{
	for (CropPlot* cp : _pCropPlotObjects)
	{
		if (cp == plot)
		{
			//GameObject* plotChild = plot->GetChild();
			//if (plotChild != nullptr)
			//{
			//	plotChild->SetToBeDestroyed(true);
			//}
			//
			//_pCropPlotObjects.erase(std::remove(_pCropPlotObjects.begin(), _pCropPlotObjects.end(), plot), _pCropPlotObjects.end());
			//plot->SetToBeDestroyed(true);
		}
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
