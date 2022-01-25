#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(GameObject* parent) : Component(parent)
{
	SetType(Component::Texture_Type);
	SetCategory(Component::Graphics_Category);
	_pSprite = new Texture2D(parent);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::OnStart()
{
}

void SpriteComponent::OnUpdate()
{
}

void SpriteComponent::OnEnd()
{
}

void SpriteComponent::DrawEditorUI()
{
}
