#include "pch.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(GameObject* parent, int drawOrder) : Component(parent), _drawOrder(drawOrder)
{
	SetType(Component::SpriteType);
	SetCategory(Component::Graphics_Category);
	//sets default coord
	_pUVSpriteCoords = new glm::vec2[4];
	_pUVSpriteCoords[0] = glm::vec2(0,0);
	_pUVSpriteCoords[1] = glm::vec2(1,0);
	_pUVSpriteCoords[2] = glm::vec2(1,1);
	_pUVSpriteCoords[3] = glm::vec2(0,1);
	//creates new texture sprite
	//_pSprite = new Texture2D(parent);
}



//sets position
void SpriteComponent::SetPosition(glm::vec2 position)
{
	_mPosX = position.x;
	_mPosY = position.y;
}

//sets size of sprite sheet for texture
void SpriteComponent::SetSpriteSheetScale(glm::vec2 scale)
{
	_mSheetWidth = scale.x;
	_mSheetHeight = scale.y;
}

//sets scale of texture sprite
void SpriteComponent::SetSpriteScale(glm::vec2 scale)
{
	_mSpriteWidth = scale.x;
	_mSpriteHeight = scale.y;
}

//sets sprite
void SpriteComponent::SetSprite(Sprite* sprite)
{
	_pSprite = sprite;
}

//sets uv coords to class values
void SpriteComponent::SetUVCoords()
{
	_pUVSpriteCoords[0] = glm::vec2((_mPosX * _mSpriteWidth) / _mSheetWidth, (_mPosY * _mSpriteHeight) / _mSheetHeight);
	_pUVSpriteCoords[1] = glm::vec2(((_mPosX + 1) * _mSpriteWidth) / _mSheetWidth, (_mPosY * _mSpriteHeight) / _mSheetHeight);
	_pUVSpriteCoords[2] = glm::vec2(((_mPosX + 1) * _mSpriteWidth) / _mSheetWidth, ((_mPosY + 1) * _mSpriteHeight) / _mSheetHeight);
	_pUVSpriteCoords[3] = glm::vec2((_mPosX * _mSpriteWidth) / _mSheetWidth, ((_mPosY + 1) * _mSpriteHeight) / _mSheetHeight);
}

//allows the ability to set uv coords manually
void SpriteComponent::SetUVCoords(glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight)
{
	_pUVSpriteCoords[0] = bottomLeft;
	_pUVSpriteCoords[1] = bottomRight;
	_pUVSpriteCoords[2] = topRight;
	_pUVSpriteCoords[3] = topLeft;
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
	if (ImGui::CollapsingHeader("Sprite"))
	{
		ImGui::Image((void*)_pSprite->GetTexture()->GetID(), ImVec2(100, 100));
		float editorPos[1];
		ImGui::InputFloat2("Position", editorPos);
		SetPosition(glm::vec2(editorPos[0], editorPos[1]));
		float editorSheetScale[1];
		ImGui::InputFloat2("Position", editorSheetScale);
		SetSpriteSheetScale(glm::vec2(editorSheetScale[0], editorSheetScale[1]));
		float editorSpriteScale[1];
		ImGui::InputFloat2("Position", editorSpriteScale);
		SetSpriteScale(glm::vec2(editorSpriteScale[0], editorSpriteScale[1]));
	}
}
