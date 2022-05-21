#include "StructureFighter.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "Time.h"
#include "SceneManager.h"
#include "DestroyAfterSecondsComponent.h"

StructureFighter::StructureFighter(GameObject* owner)
	: Component(owner)
{
	SetType(StructureFighter_Type);
}

void StructureFighter::Attack(GameObject* pTarget)
{
	if (_timeSinceLastAttack < _attackRate) return;

	_timeSinceLastAttack = 0.0f;

	glm::vec2 towerPos = GetParent()->GetTransform()->GetPosition();
	glm::vec2 directionToTarget = pTarget->GetTransform()->GetPosition() - towerPos;

	GameObject* newProjectile = new GameObject("Projectile", "PROJECTILE");
	//newProjectile->AddComponent(ResourceManager::GetTexture("lenna"));
	newProjectile->AddComponent(new Texture2D("lenna3.jpg"));
	newProjectile->GetTransform()->SetScale({ 0.15f,0.15f });
	newProjectile->GetTransform()->SetPosition(towerPos);
	newProjectile->AddComponent(new BoxColliderComponent(newProjectile))->SetTrigger(true);
	newProjectile->AddComponent(new DestroyAfterSecondsComponent(newProjectile, 5.0f));
	
	
	MovementComponent* mc = newProjectile->AddComponent(new MovementComponent(newProjectile));


	mc->SetConstantlyMove(true);
	mc->SetMoveDirection(directionToTarget);
	mc->SetAllowCollisions(false);

	SceneManager::GetCurrentScene()->AddGameObject(newProjectile);

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
