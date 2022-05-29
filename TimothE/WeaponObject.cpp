#include "pch.h"
#include "WeaponObject.h"
#include "WeaponComponent.h"

WeaponObject::WeaponObject(std::string name /*= "Weapon"*/, std::string tag /*= "WEAPON"*/) : GameObject(name, tag)
{
	_pWeaponComp = AddComponent(new WeaponComponent(this));
}

void WeaponObject::UniqueLogic()
{
	if(_pTransform != nullptr && _pParent != nullptr)
		_pTransform->SetPosition(_pParent->GetTransform()->GetForward() * 0.25f);
}
