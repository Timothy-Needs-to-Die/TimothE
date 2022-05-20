#include "StructureFighter.h"
#include "Time.h"

StructureFighter::StructureFighter(GameObject* owner)
	: Component(owner)
{
	SetType(StructureFighter_Type);
}

void StructureFighter::Attack(GameObject* pTarget)
{
	if (_timeSinceLastAttack < _attackRate) return;

	_timeSinceLastAttack = 0.0f;


}

void StructureFighter::OnUpdate()
{
	_timeSinceLastAttack += Time::GetDeltaTime();
}
