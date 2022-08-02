#include "pch.h"
#include "ProjectileObject.h"
#include "MovementComponent.h"
#include "BoxColliderComponent.h"
#include "DestroyAfterSecondsComponent.h"
#include "EnemyHealth.h"
#include "SceneManager.h"

ProjectileObject::ProjectileObject(glm::vec2 spawnPosition, glm::vec2 direction, GameObject* owner, std::string name /*= "PROJECTILE"*/, std::string tag /*= "PROJECTILE"*/)
	: GameObject(name, tag), _pOwningTower(owner)
{
	//AddComponent(ResourceManager::GetTexture("fireball"));
	_pTransform->SetScale({ 0.15f,0.15f });
	_pTransform->SetPosition(spawnPosition);

	AddComponent(new BoxColliderComponent(this))->SetTrigger(true);
	AddComponent(new DestroyAfterSecondsComponent(this, 5.0f));


	MovementComponent* mc = AddComponent(new MovementComponent(this));
	mc->SetConstantlyMove(true);
	mc->SetMoveDirection(direction);
	mc->SetAllowCollisions(false);
}

void ProjectileObject::UniqueLogic()
{

}

void ProjectileObject::OnTriggerEnter(ColliderBase* other)
{
	if (other->GetOwner()->GetTag() == "TOWER") return;

	if (other->GetOwner()->GetTag() == "ENEMY") {
		other->GetOwner()->GetComponent<EnemyHealth>()->TakeDamage(5.0f, _pOwningTower);
	}
	//else if (other->GetParent()->GetTag() == "PLAYER") {
	//	other->GetParent()->GetComponent<Health>()->TakeDamage(5.0f);
	//}


	SceneManager::GetCurrentScene()->RemoveGameObject(this);
}
