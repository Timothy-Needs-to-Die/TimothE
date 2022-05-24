#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "TileMap.h"
#include "Time.h"
#include "SceneManager.h"
#include "Player.h"



class AIController : public Component
{

public:
	AIController(GameObject* gameObject);

	COMPONENT_STATIC_TYPE(AIControllerType);

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	void SetTargetTags(std::string tagA, std::string tagB, std::string tagC);
	void FindTarget();
	void SetTarget(GameObject* target);
	void AttackedBy(GameObject* instigator);

private:
	class Fighter* _pFighter = nullptr;
	GameObject* _pCurrentTarget = nullptr;
	string _mTargetArr[3];
	Player* _pPlayer;
	GameObject* FindClosestTargetFromList(std::vector<GameObject*> targets);

	class Transform* _pPlayerTransform = nullptr;
	class Transform* _pOwnerTransform = nullptr;
	class Transform* _pTargetTransform = nullptr;
};

