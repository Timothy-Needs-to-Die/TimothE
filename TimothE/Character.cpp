#include "pch.h"
#include "Character.h"
#include "AnimatedSpritesheet.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "AudioSource.h"
#include "SceneManager.h"

Character::Character(std::string texture, std::string name, std::string tag) 
	: GameObject(name, tag) 
{
	_pAnimSheet = new AnimatedSpritesheet(ResourceManager::GetTexture(texture), 16, 32);

	GameObject* pArms = new GameObject("Arms");
	_pArmSc = pArms->AddComponent(new SpriteComponent(pArms, 110));
	_pArmSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(0));

	pArms->SetParent(this);
	pArms->GetTransform()->SetPosition({ 0.0f,0.0f });
	pArms->GetTransform()->SetScale({ 0.25f, 0.45f });

	SceneManager::GetCurrentScene()->AddGameObject(pArms);

	_pAudioSource = AddComponent(new AudioSource(this));
	_pMovement = AddComponent(new MovementComponent(this));
	_pMovement->SetMovementSpeed(1.0f);
	_pSc = AddComponent<SpriteComponent>(new SpriteComponent(this, 100));
	_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(0));
	_pAnimSheet->SetFramerate(4);
	_pTransform->SetScale({ 0.25f, 0.45f });

	_pMoveDown = new Animation();
	_pMoveDown->AddAnimationID(0);
	_pMoveDown->AddAnimationID(1);
	_pMoveDown->AddAnimationID(2);
	_pMoveDown->AddAnimationID(3);

	_pMoveRight = new Animation();
	_pMoveRight->AddAnimationID(16);
	_pMoveRight->AddAnimationID(17);
	_pMoveRight->AddAnimationID(18);
	_pMoveRight->AddAnimationID(19);

	_pMoveUp = new Animation();
	_pMoveUp->AddAnimationID(32);
	_pMoveUp->AddAnimationID(33);
	_pMoveUp->AddAnimationID(34);
	_pMoveUp->AddAnimationID(35);

	_pMoveLeft = new Animation();
	_pMoveLeft->AddAnimationID(48);
	_pMoveLeft->AddAnimationID(49);
	_pMoveLeft->AddAnimationID(50);
	_pMoveLeft->AddAnimationID(51);

	_pArmDown = new Animation();
	_pArmDown->AddAnimationID(4);
	_pArmDown->AddAnimationID(5);
	_pArmDown->AddAnimationID(6);
	_pArmDown->AddAnimationID(7);

	_pArmRight = new Animation();
	_pArmRight->AddAnimationID(20);
	_pArmRight->AddAnimationID(21);
	_pArmRight->AddAnimationID(22);
	_pArmRight->AddAnimationID(23);

	_pArmUp = new Animation();
	_pArmUp->AddAnimationID(36);
	_pArmUp->AddAnimationID(37);
	_pArmUp->AddAnimationID(38);
	_pArmUp->AddAnimationID(39);

	_pArmLeft = new Animation();
	_pArmLeft->AddAnimationID(52);
	_pArmLeft->AddAnimationID(53);
	_pArmLeft->AddAnimationID(54);
	_pArmLeft->AddAnimationID(55);

	_pArmAttack = new Animation();
	_pArmAttack->AddAnimationID(68);
	_pArmAttack->AddAnimationID(69);
	_pArmAttack->AddAnimationID(70);
	_pArmAttack->AddAnimationID(71);

	_pCurrentAnimation = _pMoveDown;
	_pCurrentArmAnimation = _pArmDown;
}

void Character::UniqueLogic()
{
	_pCurrentAnimation->Update();
	_pCurrentArmAnimation->Update();

	_pAnimSheet->Update();

	int currentRow = _pAnimSheet->GetCurrentRow();

	Direction playerDirection = _pMovement->GetDirection();

	switch (playerDirection)
	{
	case Direction::UP:
		_pCurrentAnimation = _pMoveUp;
		_pCurrentArmAnimation = _pArmUp;
		break;
	case Direction::DOWN:
		_pCurrentAnimation = _pMoveLeft;
		_pCurrentArmAnimation = _pArmLeft;
		break;
	case Direction::LEFT:
		_pCurrentAnimation = _pMoveDown;
		_pCurrentArmAnimation = _pArmDown;
		break;
	case Direction::RIGHT:
		_pCurrentAnimation = _pMoveRight;
		_pCurrentArmAnimation = _pArmRight;
		break;
	default:
		break;
	}

	if (!_pMovement->IsMoving()) {
		_pCurrentAnimation->SetIndex(0);
		
		if(!_isAttacking) _pCurrentArmAnimation->SetIndex(0);
	}

	if (_isAttacking) {
		_pCurrentArmAnimation = _pArmAttack;
	}

	_pSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(_pCurrentAnimation->GetCurrentID()));
	_pArmSc->SetSprite(_pAnimSheet->GetSpriteAtIndex(_pCurrentArmAnimation->GetCurrentID()));
}
