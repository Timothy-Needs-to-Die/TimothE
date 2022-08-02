#include "pch.h"
#include "Fighter.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Health.h"
#include "GameObject.h"
#include "WeaponComponent.h"
#include "Transform.h"
#include "AudioSource.h"
#include "Character.h"

Fighter::Fighter(GameObject* pOwner) : Component(pOwner)
{
	SetType(Component::Types::Fighter_Type);
	
	_pWeaponComponent = dynamic_cast<WeaponComponent*>(_pOwner->GetComponentInChild("Weapon", Weapon_Type));
}

void Fighter::Attack(GameObject* instigator)
{
	if (!_canAttack) return;
	//_pWeaponComponent->EndAttack();


	Character* pOwningCharacter = dynamic_cast<Character*>(_pOwner);
	if (pOwningCharacter != nullptr) {
		pOwningCharacter->SetAttacking(true);
	}

	_pWeaponComponent->StartAttack();

	instigator->GetComponent<AudioSource>()->PlaySound("SwordSlash", 0.2, 0.3, 0.6, 1.0);
	_canAttack = false;
	TIM_LOG_LOG("Attacking");

	//Find all objects with a health component atached to them in scene
	std::vector<Health*> healthObjects = SceneManager::GetCurrentScene()->FindObjectsOfType<Health>();

	//Stores all the nearby health objects
	std::vector<Health*> nearbyHealthObjects;

	//Stores the fighters position, reduces memory access
	glm::vec2 fighterPos = _pOwner->GetTransform()->GetPosition();


	//Cache the weapon range to reduce memory access
	float weaponRange = _weaponConfig.range;

	//Cycles through all health objects
	for (auto& h : healthObjects) {
		if (h->GetOwner() == _pOwner) continue;

		//Get the position of this health object
		glm::vec2 hPos = h->GetOwner()->GetTransform()->GetPosition();

		//if the distance between them is less than our weapons range
		if (glm::distance(fighterPos, hPos) < weaponRange) {
			//emplace into the nearby health objects vector
			nearbyHealthObjects.emplace_back(h);
		}
	}


	glm::vec2 fighterForward = _pOwner->GetTransform()->GetForward();

	//Cycles through each nearby health object
	for (auto& obj : nearbyHealthObjects) {
		//Calculate the direction vector
		glm::vec2 dir = obj->GetOwner()->GetTransform()->GetPosition() - fighterPos;
		
		float dot = glm::dot(dir, fighterForward);

		if (dot >= 0.05f) {
			obj->TakeDamage(_weaponConfig.damage, instigator);
		}
	}

}

void Fighter::OnUpdate()
{
	if (!_canAttack) {
		_timeSinceLastAttack += Time::GetDeltaTime();

		if (_timeSinceLastAttack > _weaponConfig.attackSpeed) {
			_timeSinceLastAttack = 0.0f;
			_canAttack = true;
			
			_pWeaponComponent->EndAttack();

			Character* pOwningCharacter = dynamic_cast<Character*>(_pOwner);
			if (pOwningCharacter != nullptr) {
				pOwningCharacter->SetAttacking(false);
			}
		}
	}

}
