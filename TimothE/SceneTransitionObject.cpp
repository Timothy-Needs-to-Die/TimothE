#include "pch.h"
#include "SceneTransitionObject.h"
#include "Core.h"
#include "ColliderBase.h"
#include "BoxColliderComponent.h"
#include "SceneManager.h"

SceneTransitionObject::SceneTransitionObject(std::string destination, std::string name /*= "SceneTransitionObject"*/, std::string tag /*= "TRANSITION_POINT"*/)
	: GameObject(name, tag), _destination(destination)
{

	//Creates a box collider that's a trigger and will only intersect with the player
	_pBoxCollider = AddComponent(new BoxColliderComponent(this));
	_pBoxCollider->SetTrigger(true);
	_pBoxCollider->SetCollidersChannel(CollisionChannel_SceneTransition);
	_pBoxCollider->AddCompatibleChannel(CollisionChannel_Player);
}

void SceneTransitionObject::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetOwner()->GetTag() == "PLAYER") {
		TIM_LOG_LOG("Should Transition to other scene");

		//turns D_EastPlains_Sp1 into EastPlains_Sp1
		std::string sceneName = _destination.substr(2);

		std::string cache = sceneName;

		//Turns EastPlains_Sp1 into EastPlains
		sceneName = sceneName.substr(0, sceneName.find("_"));

		//Creates S_EastPlains_Sp1
		std::string finishedString = "S_" + cache;

		
		glm::vec2 spawnPos = SceneManager::GetScene(sceneName)->GetSpawnPosition(finishedString);

		//TIM_LOG_LOG("Scene Name: " << sceneName << " Spawn Point Name: " << finishedString << " Spawn Position: " << spawnPos.x << ", " << spawnPos.y);

		SceneManager::SetCurrentScene(sceneName, spawnPos);
	}
}
