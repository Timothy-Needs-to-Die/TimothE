#include "Fighter.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Health.h"
#include "GameObject.h"
#include "Transform.h"

void Fighter::Attack(GameObject* instigator)
{
	if (!_canAttack) return;
	_canAttack = false;


	//Find all objects with a health component atached to them in scene
	std::vector<Health*> healthObjects = SceneManager::GetCurrentScene()->FindObjectsOfType<Health>();

	//Stores all the nearby health objects
	std::vector<Health*> nearbyHealthObjects;

	//Stores the fighters position, reduces memory access
	glm::vec2 fighterPos = _pParentObject->GetTransform()->GetPosition();


	//Cache the weapon range to reduce memory access
	float weaponRange = _weaponConfig.range;

	//Cycles through all health objects
	for (auto& h : healthObjects) {
		if (h->GetParent() == _pParentObject) continue;

		//Get the position of this health object
		glm::vec2 hPos = h->GetParent()->GetTransform()->GetPosition();

		//if the distance between them is less than our weapons range
		if (glm::distance(fighterPos, hPos) < weaponRange) {
			//emplace into the nearby health objects vector
			nearbyHealthObjects.emplace_back(h);
		}
	}


	glm::vec2 fighterForward = _pParentObject->GetTransform()->GetForward();

	//Cycles through each nearby health object
	for (auto& obj : nearbyHealthObjects) {
		

		//Calculate the direction vector
		glm::vec2 dir = obj->GetParent()->GetTransform()->GetPosition() - fighterPos;
		
		float dot = glm::dot(dir, fighterForward);

		

		//std::cout << "Dot: " << dot << std::endl;

		if (dot >= 0.0f) {
			obj->TakeDamage(_weaponConfig.damage, instigator);
			//std::cout << "Would hit!" << std::endl;
		}
		else {
			//std::cout << "Would not hit!" << std::endl;
		}
	}

}

void Fighter::OnStart()
{
}

void Fighter::OnUpdate()
{
	if (!_canAttack) {
		_timeSinceLastAttack += Time::GetDeltaTime();

		if (_timeSinceLastAttack > _weaponConfig.attackSpeed) {
			_timeSinceLastAttack = 0.0f;
			_canAttack = true;
		}
	}

}

void Fighter::OnEnd()
{
}
