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

void PlayerInputComponent::OnStart()
{
	_pMovement = _pParentObject->GetComponent<MovementComponent>();
	_pFighter = _pParentObject->GetComponent<Fighter>();
}

void PlayerInputComponent::OnUpdate()
{
	MoveControls();

	if (_pFighter == nullptr) {
		TIM_LOG_ERROR("Player does not have fighter component attached");
		return;
	}

	if (Input::IsKeyDown(KEY_SPACE)) {
		_pFighter->Attack();
	}

	if (_pNearbyResourceNode != nullptr) {
		if (Input::IsMouseButtonDown(BUTTON_1)) {
			_pNearbyResourceNode->Interact();
		}
	}

	if (Input::IsKeyDown(KEY_I)) {
		int goldAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Gold)->GetAmount();
		int woodAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Wood)->GetAmount();
		int metalAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Metal)->GetAmount();
		int stoneAmount = PlayerResourceManager::GetCoreResource(CoreResourceType::Stone)->GetAmount();

		TIM_LOG_LOG("Gold: " << goldAmount);
		TIM_LOG_LOG("Wood: " << woodAmount);
		TIM_LOG_LOG("Metal: " << metalAmount);
		TIM_LOG_LOG("Stone: " << stoneAmount);
	}

	if (Input::IsKeyUp(KEY_B)) {
		_bReadyforbuildPress = true;
	}

	if (_bReadyforbuildPress && Input::IsKeyDown(KEY_B)) {
		_bReadyforbuildPress = false;
		_inBuildMode = !_inBuildMode;
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

	CameraManager::GetCamera(-1)->SetPosition({ _pParentObject->GetTransform()->GetPosition(), -2.0f });
}

void PlayerInputComponent::BuildControls()
{
	FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());
	if (pFarmScene == nullptr) return;

	TileMap* pTilemap = pFarmScene->GetTileMap();

	if (Input::IsKeyDown(KEY_1)) {
		_selectedStructure = StructureType::Wall;
	}
	else if (Input::IsKeyDown(KEY_2)) {
		_selectedStructure = StructureType::Tower;
	}


	if (Input::IsMouseButtonDown(BUTTON_1)) {

		glm::vec2 mousePos = Input::GetMousePos();


		glm::vec2 size = CameraManager::CurrentCamera()->Size();

		glm::vec2 cameraPos = CameraManager::CurrentCamera()->PositionXY() / 2.0f;
		cameraPos *= size;
		cameraPos -= size;
		glm::vec2 convertedPos = cameraPos + mousePos;

		TIM_LOG_LOG("Converted Pos: " << convertedPos.x << ", " << convertedPos.y);



		if (convertedPos.x < 0.0f || convertedPos.y < 0.0f) return;

		ResourceCost cost;

		switch (_selectedStructure) {
		case StructureType::Wall:
			cost.woodRequired = 1;
			break;
		case StructureType::Tower:
			cost.woodRequired = 3;
			cost.stoneRequired = 5;
			break;
		default:
			return;
		}

		if (PlayerResourceManager::CanAfford(cost)) {
			glm::vec2 tilePos = pTilemap->GetTileAtWorldPos(0, convertedPos)->pos;

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
				}

				if (pObject == nullptr) {
					TIM_LOG_ERROR("pObject was nullptr");
					return;
				}

				Transform* pTransform = pObject->GetTransform();

				pTilemap->SetCollidableAtLayer(5, tilePos, true);

				pTransform->SetPosition(tilePos);
				pTransform->SetScale({ 0.25f,0.25f });

				pFarmScene->AddStructure(pObject);

				PlayerResourceManager::SpendResources(cost);

			}
		}
	}

	//FarmScene* pFarmScene = dynamic_cast<FarmScene*>(SceneManager::GetCurrentScene());
	//if (pFarmScene) {
	//	TileMap* pTilemap = pFarmScene->GetTileMap();

		//if (Input::IsKeyDown(KEY_1)) {
		//	//ResourceCost wallCost;
		//	//wallCost.woodRequired = 1;
		//
		//	//if (PlayerResourceManager::CanAfford(wallCost)) {
		//		//glm::vec2 pos = pTilemap->GetTileAtWorldPos(0, _pParentObject->GetTransform()->GetPosition())->pos;
		//
		//		if (!pTilemap->CollidableAtPosition(pos)) {
		//			StructureObject* pObject = new StructureObject("Wall", "WALL");
		//
		//			Transform* pTransform = pObject->GetTransform();
		//
		//			pTilemap->SetCollidableAtLayer(5, pos, true);
		//
		//			pTransform->SetPosition(pos);
		//			pTransform->SetScale({ 0.25f,0.25f });
		//
		//			pFarmScene->AddStructure(pObject);
		//
		//			PlayerResourceManager::SpendResources(wallCost);
		//		}
		//	}
		//}
		//
		//if (Input::IsKeyDown(KEY_2)) {
		//	//ResourceCost towerCost;
		//	//towerCost.woodRequired = 3;
		//	//towerCost.stoneRequired = 5;
		//
		//	//if (PlayerResourceManager::CanAfford(towerCost)) {
		//		glm::vec2 pos = pFarmScene->GetTileMap()->GetTileAtWorldPos(0, _pParentObject->GetTransform()->GetPosition())->pos;
		//
		//		if (!pTilemap->CollidableAtPosition(pos)) {
		//			OffensiveStructureObject* pObject = new OffensiveStructureObject("Tower", "TOWER");
		//
		//			Transform* pTransform = pObject->GetTransform();
		//
		//			pTilemap->SetCollidableAtLayer(5, pos, true);
		//
		//			pTransform->SetPosition(pos);
		//			pTransform->SetScale({ 0.25f,0.25f });
		//
		//			pFarmScene->AddStructure(pObject);
		//
		//			PlayerResourceManager::SpendResources(towerCost);
		//		}
		//	}
		//}
	//}
}

void PlayerInputComponent::NearbyResourceNode(class ResourceNode* nearbyResource)
{
	_pNearbyResourceNode = nearbyResource;
}

void PlayerInputComponent::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "RESOURCE_NODE") {
		_pNearbyResourceNode = other->GetParent()->GetComponent<ResourceNode>();
	}
}

void PlayerInputComponent::OnTriggerExit(ColliderBase* other)
{
	if (other->GetParent()->GetTag() == "RESOURCE_NODE") {
		_pNearbyResourceNode = nullptr;
	}
}
