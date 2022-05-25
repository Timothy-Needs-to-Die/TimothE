#include "Bed.h"
#include "BedHealth.h"
#include "GameTimeManager.h"
#include "FarmScene.h"

Bed::Bed() : GameObject("Bed", "BED")
{
	_pHealth = AddComponent<BedHealth>(new BedHealth(this, 100));
	_pHealth->SetHealth(100);
	_pBoxCollider = AddComponent<BoxColliderComponent>(new BoxColliderComponent(this));
	_pBoxCollider->SetTrigger(true);
	_pTexture = AddComponent<Texture2D>(new Texture2D("whiteTexture.png", "whiteTexture"));
	_pTexture->SetParent(this);
}

Bed::~Bed()
{
}

//on triggering collision with bed
void Bed::OnTriggerEnter(ColliderBase* other)
{
	//gets day controller
	GameTimeManager* daycontroller = nullptr;
	FarmScene* scene = (FarmScene*)SceneManager::GetCurrentScene();
	daycontroller = scene->GetGameTime();

	//if day time sleep isnt possible exit out of function
	if (daycontroller->IsDay())
	{
		return;
	}

	//player collided with bed
	std::string tag = other->GetParent()->GetTag();
	if (tag == "PLAYER")
	{
		//if night cleared then sleep
		//if (daycontroller->_nightCleared)
		{
			//next day
			daycontroller->StartNewDay();
			// sleep and restore bed and player hp
			_pHealth->SetHealth(_pHealth->GetMaxHealth());
			Health* playerhealth = other->GetParent()->GetComponent<Health>();
			playerhealth->SetHealth(playerhealth->GetMaxHealth());
		}

		
	}
}


