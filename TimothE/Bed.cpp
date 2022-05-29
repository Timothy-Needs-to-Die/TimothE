#include "pch.h"
#include "Bed.h"

#include "Bed.h"
#include "BedHealth.h"
#include "GameTimeManager.h"
#include "FarmScene.h"
#include "BoxColliderComponent.h"

Bed::Bed() : GameObject("Bed", "BED")
{
	_pHealth = AddComponent<BedHealth>(new BedHealth(this, 100));
	_pHealth->SetHealth(100);
	_pBoxCollider = AddComponent<BoxColliderComponent>(new BoxColliderComponent(this));
	_pBoxCollider->SetTrigger(true);
	_pTexture = AddComponent<Texture2D>(ResourceManager::GetTexture("bed"));
	_pTexture->SetParent(this);
}

Bed::~Bed()
{
}

void Bed::UniqueLogic()
{
	if (Input::IsKeyUp(KEY_E))
	{
		_isKeyUP = true;
	}
	if (Input::IsKeyDown(TimothEKeyCode::KEY_E) && _isInRange == true && _isKeyUP) {
		_isKeyUP = false;
		GameTimeManager* daycontroller = nullptr;
		FarmScene* scene = (FarmScene*)SceneManager::GetCurrentScene();
		daycontroller = scene->GetGameTime();
		//if night cleared then sleep
		if (daycontroller->IsDay())
		{
			daycontroller->SetNight();
		}
		else if (canSleepThroughNight && !daycontroller->IsDay())//wave cleared
		{
			//next day
			scene->PlayerSlept();
			// sleep and restore bed and player hp
			_pHealth->SetHealth(_pHealth->GetMaxHealth());
			
			//playerhealth->SetHealth(playerhealth->GetMaxHealth());
			canSleepThroughNight = false;
		}
	}
}

//on triggering collision with bed
void Bed::OnTriggerEnter(ColliderBase* other)
{
	//gets day controller
	


	//player collided with bed
	std::string tag = other->GetParent()->GetTag();
	if (tag == "PLAYER")
	{
		_isInRange = true;
		//playerhealth = other->GetParent()->GetComponent<Health>();
	}
}

void Bed::OnTriggerExit(ColliderBase* other)
{
	std::string tag = other->GetParent()->GetTag();
	if (tag == "PLAYER")
	{
		_isInRange = true;
	}
}


