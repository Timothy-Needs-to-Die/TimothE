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
		_pFighter->Attack(_pParentObject);
	}

	if (_pNearbyResourceNode != nullptr) {
		if (Input::IsMouseButtonDown(BUTTON_1)) {
			_pNearbyResourceNode->Interact();
		}
	}
	//testing game over
	if (Input::IsKeyDown(KEY_H)) {
		_pParentObject->GetComponent<PlayerHealth>()->TakeDamage(10000, NULL);
		TIM_LOG_LOG(_pParentObject->GetComponent<PlayerHealth>()->GetCurrentHealth());
	}

	if (Input::IsKeyUp(KEY_B)) {
		_bReadyforbuildPress = true;
	}

	if (_bReadyforbuildPress && Input::IsKeyDown(KEY_B)) {
		_bReadyforbuildPress = false;
		_inBuildMode = !_inBuildMode;
		GameObject* pBBuildText = SceneManager::GetCurrentScene()->FindObjectWithTag("BUILDMODETEXT");
		PlayerUIComponent* pUI = _pParentObject->GetComponent<PlayerUIComponent>();
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
	else if (Input::IsKeyDown(KEY_3)) {
		TIM_LOG_LOG("Selected campfire");
		_selectedStructure = StructureType::Campfire;
	}

	glm::vec2 mousePos = Input::GetMousePos();
	glm::vec2 size = CameraManager::CurrentCamera()->Size();
	glm::vec2 convertedPos = _pParentObject->GetTransform()->GetPosition() + (mousePos * size);

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

			//pTilemap->SetCollidableAtLayer(5, tilePos, false);

			pFarmScene->RemoveStructure(structuresInScene[i]);

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
