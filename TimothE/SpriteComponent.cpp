#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(GameObject* parent) : Component(parent)
{
	SetType(Component::Texture_Type);
	SetCategory(Component::Graphics_Category);
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
