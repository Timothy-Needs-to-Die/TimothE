#include "Bed.h"
#include "BedHealth.h"
#include "SceneManager.h"
#include "GameTimeManager.h"
#include "FarmScene.h"

Bed::Bed() : GameObject("Bed", "BED")
{
	_pHealth = AddComponent<BedHealth>(new BedHealth(this));
	_pHealth->SetHealth(100);
	_pBoxCollider = AddComponent<BoxColliderComponent>(new BoxColliderComponent(this));
	_pBoxCollider->SetTrigger(true);
	_pTexture = AddComponent<Texture2D>(new Texture2D("whiteTexture.png", "whiteTexture"));
	_pTexture->SetParent(this);
}

Bed::~Bed()
{
}

void Bed::OnTriggerEnter(ColliderBase* other)
{
	GameTimeManager* daycontroller = nullptr;
	if (SceneManager::GetCurrentScene()->GetName() == "FarmScene")
	{
		FarmScene* scene = (FarmScene*)SceneManager::GetCurrentScene();
		daycontroller = scene->GetGameTime();
	}

	if (daycontroller->IsDay())
	{
		return;
	}

	std::string tag = other->GetParent()->GetTag();
	if (tag == "ENEMY"/* || tag == "PLAYER"*/)
	{
		// enemy attack
		// todo replace this
		_pHealth->TakeDamage(100);
	}
	else if (tag == "PLAYER")
	{
		std::vector<GameObject*> objects = SceneManager::GetCurrentScene()->GetGameObjects();
		for (GameObject* go : objects)
		{
			if (go->GetTag() == "ENEMY")
			{
				return;
			}
		}
		// sleep and restore bed and player hp
		daycontroller->StartNewDay();
		_pHealth->SetHealth(_pHealth->GetMaxHealth());
		Health* playerhealth = other->GetParent()->GetComponent<Health>();
		playerhealth->SetHealth(playerhealth->GetMaxHealth());
	}
}
