#include "pch.h"
#include "PlayerInputComponent.h"
#include "CameraManager.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "ResourceNode.h"
#include "PlayerResourceManager.h"
#include "PurchaseableConfig.h"
#include "FarmScene.h"
#include "StructureObject.h"
#include "OffensiveStructureObject.h"
#include "LightsourceObject.h"
#include "PlayerHealth.h"
#include "PlayerUIComponent.h"
#include "AudioSource.h"

#include "TileData.h"
#include "TileMap.h"
#include "MovementComponent.h"
#include "Fighter.h"
#include "FarmlandManager.h"

void PlayerInputComponent::OnStart()
{
	_pMovement = _pOwner->GetComponent<MovementComponent>();
	_pFighter = _pOwner->GetComponent<Fighter>();
	_pFarmlandManager = _pOwner->GetComponent<FarmlandManager>();
	_pFarmlandManager->LoadInCropData();
}

void PlayerInputComponent::OnUpdate()
{
	MoveControls();

	if (_pFighter == nullptr) {
		TIM_LOG_ERROR("Player does not have fighter component attached");
		return;
	}

	// Fighting
	if (Input::IsKeyPressedOnce(KEY_SPACE)) {
		_pFighter->Attack(_pOwner);

	}

	// Resource Gathering
	if (_pNearbyResourceNode != nullptr) {
		if (Input::IsMouseButtonDown(BUTTON_1)) {
			_pNearbyResourceNode->Interact();
		}
	}

	FarmingControls();


	if (Input::IsKeyPressedOnce(KEY_B)) {
		_inBuildMode = !_inBuildMode;
		PlayerUIComponent* pUI = _pOwner->GetComponent<PlayerUIComponent>();
		if (pUI) {
			pUI->SetBuildModeUIActive(_inBuildMode);
		}
		else {
			TIM_LOG_LOG("No build text");
		}

		TIM_LOG_LOG("In Build Mode: " << _inBuildMode);
	}


	if (_inBuildMode) {
		BuildControls();
	}

}

void PlayerInputComponent::OnEnd()
{

}

void PlayerInputComponent::MoveControls()
{
	if (_pMovement == nullptr) {
		TIM_LOG_ERROR("Character does not have movement component attached");
		return;
	}

	glm::vec2 moveVec = glm::vec2(0.0f);

	if (Input::IsKeyHeld(KEY_W)) {
		moveVec.y = 1.0f;
	}
	else if (Input::IsKeyHeld(KEY_S)) {
		moveVec.y = -1.0f;
	}

	if (Input::IsKeyHeld(KEY_A)) {
		moveVec.x = -1.0f;
	}
	else if (Input::IsKeyHeld(KEY_D)) {
		moveVec.x = 1.0f;
	}

	
	_pMovement->Move(moveVec);
	
	//CameraManager::MainCamera()->SetPosition({ _pParentObject->GetTransform()->GetPosition(), -2.0f });
}

void PlayerInputComponent::FarmingControls()
{
	// Farming

	// Harvesitng / Tilling Land
	if (Input::IsKeyPressedOnce(KEY_F))
	{

		// Get our players pos
		glm::vec2 target = _pOwner->GetTransform()->GetPosition();
		// Targets the midpoint of the player
		target.x += _pOwner->GetTransform()->GetScale().x / 2;
		target.y += _pOwner->GetTransform()->GetScale().y / 2;
		
		GetOwner()->GetComponent<AudioSource>()->PlaySound("PlantSeed", 0.4, 0.5, 1, 1);
		// If we cant place farm land
		if (!_pFarmlandManager->PlaceFarmLand(target))
		{
			// Lets try harvest land
			CropPlot* closestPlot = _pFarmlandManager->GetCropPlotAtPosition(target);
			if (closestPlot != nullptr)
			{
				if (closestPlot->IsOccupied())
				{
					// If theres a closest plot "under the player" and it has a crop try to harvest it
					_pFarmlandManager->HarvestPlot(closestPlot);
				}
				else
				{
					// Untill the ground if theres no crops in the farmland
					_pFarmlandManager->RemoveCropPlot(closestPlot);
				}
			}
		}
	}
	// Farming mode Toggle
	if (Input::IsKeyPressedOnce(KEY_G))
	{
		if (_inBuildMode) { return; }

		_bFarmMode = !_bFarmMode;
		PlayerUIComponent* pUI = _pOwner->GetComponent<PlayerUIComponent>();
		if (pUI) {
			pUI->SetFarmModeUIActive(_bFarmMode);
		}
	}

	if (_bFarmMode)
	{
		// Plant Wheat
		if (Input::IsKeyPressedOnce(KEY_1)) {
			glm::vec2 playerPos = _pOwner->GetTransform()->GetPosition();
			_pFarmlandManager->PlantSeed(GetPlayerMidpoint(playerPos), PlantResourceType::WheatSeedRes);
			//GetParent()->GetComponent<AudioSource>()->PlaySound("PlantSeed", 50, 60, 1, 1);

		}
		// Plant Potato
		else if (Input::IsKeyPressedOnce(KEY_2)) {
			glm::vec2 playerPos = _pOwner->GetTransform()->GetPosition();
			_pFarmlandManager->PlantSeed(GetPlayerMidpoint(playerPos), PlantResourceType::PotatoSeedRes);
			//GetParent()->GetComponent<AudioSource>()->PlaySound("PlantSeed", 50, 60, 1, 1);

		}
		// Plant Carrot
		else if (Input::IsKeyPressedOnce(KEY_3)) {
			glm::vec2 playerPos = _pOwner->GetTransform()->GetPosition();
			_pFarmlandManager->PlantSeed(GetPlayerMidpoint(playerPos), PlantResourceType::CarrotSeedRes);
			//GetParent()->GetComponent<AudioSource>()->PlaySound("PlantSeed", 50, 60, 1, 1);

		}
		else if (Input::IsKeyPressedOnce(KEY_4))
		{
			glm::vec2 playerPos = _pOwner->GetTransform()->GetPosition();
			//GetParent()->GetComponent<AudioSource>()->PlaySound("PlantSeed", 50, 60, 1, 1);

			CropPlot* closestPlot = _pFarmlandManager->GetCropPlotAtPosition(GetPlayerMidpoint(playerPos));
			_pFarmlandManager->RemoveCropPlot(closestPlot);
		}
		else if (Input::IsKeyPressedOnce(KEY_F1))
		{
			PlayerResourceManager::BuyCrop(WheatSeedRes);
		}
		else if (Input::IsKeyPressedOnce(KEY_F2))
		{
			PlayerResourceManager::BuyCrop(PotatoSeedRes);
		}
		else if (Input::IsKeyPressedOnce(KEY_F3))
		{
			PlayerResourceManager::BuyCrop(CarrotSeedRes);
		}
		else if (Input::IsKeyPressedOnce(KEY_F4))
		{
			GetOwner()->GetComponent<AudioSource>()->PlaySound("CashRegister", 0.4, 0.5, 1, 1);
			PlayerResourceManager::SellAll();

		}
	}
}

void PlayerInputComponent::BuildControls()
{
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());
	if (pFarmScene == nullptr) return;

	TileMap* pTilemap = pFarmScene->GetTileMap();

	if (Input::IsKeyPressedOnce(KEY_1)) {
		_selectedStructure = StructureType::Wall;
	}
	else if (Input::IsKeyPressedOnce(KEY_2)) {
		_selectedStructure = StructureType::Tower;
	}
	else if (Input::IsKeyPressedOnce(KEY_3)) {
		TIM_LOG_LOG("Selected campfire");
		_selectedStructure = StructureType::Campfire;
	}

	glm::vec2 mousePos = Input::GetMousePos();
	glm::vec2 size = CameraManager::CurrentCamera()->Size();
	glm::vec2 convertedPos = _pOwner->GetTransform()->GetPosition() + (mousePos * size);

	if (convertedPos.x < 0.0f || convertedPos.y < 0.0f) return;
	
	glm::vec2 tilePos = pTilemap->GetTileAtWorldPos(0, convertedPos)->pos;

	if (Input::IsMouseButtonDown(BUTTON_1)) {
		ResourceCost cost;

		switch (_selectedStructure) {
		case StructureType::Wall:
			cost.woodRequired = 1;
			
			break;
		case StructureType::Tower:
			cost.woodRequired = 3;
			cost.stoneRequired = 5;
			
			break;
		case StructureType::Campfire:
			cost.woodRequired = 3;
			cost.coalRequired = 2;
			
			break;
		default:
			TIM_LOG_WARNING("Case not covered");
			return;
		}

		//if (PlayerResourceManager::CanAfford(cost)) {

			if (!pTilemap->CollidableAtPosition(tilePos)) {
				StructureObject* pObject;

				switch (_selectedStructure)
				{
				case StructureType::Wall:
					pObject = new StructureObject("Wall", "WALL");
					break;
				case StructureType::Tower:
					pObject = new OffensiveStructureObject("Tower");
					break;
				case StructureType::Campfire:
					TIM_LOG_LOG("Creating lightsource");
					pObject = new LightsourceObject(tilePos);
					break;
				}

				if (pObject == nullptr) {
					TIM_LOG_ERROR("pObject was nullptr");
					return;
				}

				Transform* pTransform = pObject->GetTransform();
				pTransform->SetPosition(tilePos);

				pFarmScene->AddStructure(pObject);

				GetOwner()->GetComponent<AudioSource>()->PlaySound("BuildSound", 0.4, 0.5, 0.9, 1.0);
				//PlayerResourceManager::SpendResources(cost);


				//PlayerResourceManager::SpendResources(cost);


			}
		//}
	}

	if (Input::IsMouseButtonDown(BUTTON_RIGHT)) {
		std::vector<StructureObject*> structuresInScene = pFarmScene->GetStructures();

		if (structuresInScene.empty()) return;

		for (int i = 0; i < structuresInScene.size(); ++i) {
			glm::vec2 pos = structuresInScene[i]->GetTransform()->GetPosition();

			if (pos != tilePos) continue;

			pFarmScene->RemoveStructure(structuresInScene[i]);
			GetOwner()->GetComponent<AudioSource>()->PlaySound("BuildSound", 0.4, 0.5, 0.9, 1.0);


			break;
		}
	}
}

void PlayerInputComponent::NearbyResourceNode(class ResourceNode* nearbyResource)
{
	_pNearbyResourceNode = nearbyResource;
}

void PlayerInputComponent::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetOwner()->GetTag() == "RESOURCE_NODE") {
		_pNearbyResourceNode = other->GetOwner()->GetComponent<ResourceNode>();
	}
}

void PlayerInputComponent::OnTriggerExit(ColliderBase* other)
{
	if (other->GetOwner()->GetTag() == "RESOURCE_NODE") {
		_pNearbyResourceNode = nullptr;
	}
}
