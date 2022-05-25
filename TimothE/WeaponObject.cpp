#include "WeaponObject.h"
#include "WeaponComponent.h"

WeaponObject::WeaponObject(std::string name /*= "Weapon"*/, std::string tag /*= "WEAPON"*/) : GameObject(name, tag)
{
	_pWeaponComp = AddComponent(new WeaponComponent(this));
}

void WeaponObject::UniqueLogic()
{
	glm::vec2 pos = _pParent->GetTransform()->GetPosition();

	pos += _pParent->GetTransform()->GetForward() * 0.25f;

	_pTransform->SetPosition(_pParent->GetTransform()->GetForward() * 0.25f);
}
