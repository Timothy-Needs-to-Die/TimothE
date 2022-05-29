#include "pch.h"
#include "StructureFighter.h"
#include "GameObject.h"
//#include "MovementComponent.h"
#include "Transform.h"
#include "Time.h"
#include "SceneManager.h"
//#include "DestroyAfterSecondsComponent.h"
#include "ProjectileObject.h"

StructureFighter::StructureFighter(GameObject* owner)
	: Component(owner), _timeSinceLastAttack(0.0f), _attackRate(2.5f)
{
	SetType(StructureFighter_Type);
}

void StructureFighter::Attack(GameObject* pTarget)
{
	if (pTarget == nullptr) return;
	if (!pTarget->IsActive()) return;
	if (_timeSinceLastAttack < _attackRate) return;

	_timeSinceLastAttack = 0.0f;

	glm::vec2 towerPos = _pParentObject->GetTransform()->GetPosition();
	glm::vec2 directionToTarget = glm::normalize(pTarget->GetTransform()->GetPosition() - towerPos);

	towerPos += (directionToTarget * 3.0f) / 4.0f;

	ProjectileObject* pProjectileObject = new ProjectileObject(towerPos, directionToTarget, _pParentObject);
	SceneManager::GetCurrentScene()->AddGameObject(pProjectileObject);
}

void StructureFighter::OnStart()
{
}

void StructureFighter::OnUpdate()
{
	_timeSinceLastAttack += Time::GetDeltaTime();
}

void StructureFighter::OnEnd()
{
}
