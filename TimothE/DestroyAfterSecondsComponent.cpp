#include "pch.h"
#include "DestroyAfterSecondsComponent.h"
#include "Time.h"
#include "SceneManager.h"

DestroyAfterSecondsComponent::DestroyAfterSecondsComponent(GameObject* owner, float duration /*= 5.0f*/)
	: Component(owner), _duration(duration), _timer(0.0f)
{
	SetType(Component::DestroyAfterSeconds_Type);
}

void DestroyAfterSecondsComponent::OnStart()
{

}

void DestroyAfterSecondsComponent::OnUpdate()
{
	_timer += Time::GetDeltaTime();

	if (_timer > _duration) {
		SceneManager::GetCurrentScene()->RemoveGameObject(_pOwner);
	}
}

void DestroyAfterSecondsComponent::OnEnd()
{

}
