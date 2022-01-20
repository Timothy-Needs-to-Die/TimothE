//#include "SpriteComponent.h"
//
//
//
//SpriteComponent::SpriteComponent(GameObject* parentObject)
//{
//	SetType(Component::Types::Sprite_Type);
//	SetCategory(Component::Categories::Graphics_Category);
//	_parentObject = parentObject;
//	OnStart();
//}
//
//void SpriteComponent::CreateFromTexCoords(Texture2D* texture, const glm::vec2& coords, const glm::vec2& spriteSize)
//{
//	
//	glm::vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight() };
//	glm::vec2 max = { ((coords.x + 1) * spriteSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y) / texture->GetHeight() };
//	
//}
//
//void SpriteComponent::OnStart()
//{
//}
//
//void SpriteComponent::OnUpdate()
//{
//}
//
//void SpriteComponent::OnEnd()
//{
//}
//
////void SpriteComponent::ProcessTexCoords(Texture2D& texture, const glm::vec2& min, const glm::vec2& max)
////{
////	_texture = &texture;
////
////	_texCoords[0] = { min.x, min.y };
////	_texCoords[1] = { max.x, min.y };
////	_texCoords[2] = { max.x, max.y };
////	_texCoords[3] = { min.x, max.y };
////}
