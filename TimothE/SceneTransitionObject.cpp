#include "pch.h"
#include "SceneTransitionObject.h"
#include "Core.h"
#include "ColliderBase.h"
#include "BoxColliderComponent.h"
#include "SceneManager.h"

SceneTransitionObject::SceneTransitionObject(std::string destination, std::string name /*= "SceneTransitionObject"*/, std::string tag /*= "TRANSITION_POINT"*/)
	: GameObject(name, tag)
{

	_pBoxCollider = AddComponent(new BoxColliderComponent(this));
	_pBoxCollider->SetTrigger(true);
	_pBoxCollider->SetCollidersChannel(CollisionChannel_SceneTransition);
	_pBoxCollider->AddCompatibleChannel(CollisionChannel_Player);

	_destination = destination;

}

void SceneTransitionObject::OnTriggerEnter(ColliderBase* other)
{
	if (_transitioning) return;

	if (other->GetOwner()->GetTag() == "PLAYER") {
		TIM_LOG_LOG("Should Transition to other scene");

		//turns D_EastPlains_Sp1 into EastPlains_Sp1
		std::string sceneName = _destination.substr(2);

		std::string cache = sceneName;

		int underscorePos = sceneName.find("_");

		//Turns EastPlains_Sp1 into EastPlains
		sceneName = sceneName.substr(0, underscorePos);

		//Creates S_EastPlains_Sp1
		std::string finishedString = "S_" + cache;

		
		glm::vec2 spawnPos = SceneManager::GetScene(sceneName)->GetSpawnPosition(finishedString);

		_transitioning = true;
		//TIM_LOG_LOG("Scene Name: " << sceneName << " Spawn Point Name: " << finishedString << " Spawn Position: " << spawnPos.x << ", " << spawnPos.y);

		SceneManager::SetCurrentScene(sceneName, spawnPos);


		//SceneManager::GetCurrentScene()->MovePlayerToSpawnPoint(finishedString);
	}
}
