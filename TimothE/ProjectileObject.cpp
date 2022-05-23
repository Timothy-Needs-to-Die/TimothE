#include "ProjectileObject.h"
#include "MovementComponent.h"
#include "BoxColliderComponent.h"
#include "DestroyAfterSecondsComponent.h"
#include "EnemyHealth.h"
#include "SceneManager.h"

ProjectileObject::ProjectileObject(glm::vec2 spawnPosition, glm::vec2 direction, std::string name /*= "PROJECTILE"*/, std::string tag /*= "PROJECTILE"*/)
	: GameObject(name, tag)
{
	AddComponent(new Texture2D("lenna"));
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
	if (other->GetParent()->GetTag() == "TOWER") return;

	if (other->GetParent()->GetTag() == "ENEMY") {
		other->GetParent()->GetComponent<EnemyHealth>()->TakeDamage(5.0f);
	}
	//else if (other->GetParent()->GetTag() == "PLAYER") {
	//	other->GetParent()->GetComponent<Health>()->TakeDamage(5.0f);
	//}


	SceneManager::GetCurrentScene()->RemoveGameObject(this);
}
