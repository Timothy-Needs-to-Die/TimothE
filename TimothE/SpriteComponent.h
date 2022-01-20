//
//#pragma once
//#include "Component.h"
//#include "Texture2D.h"
//#include "glm.hpp"
//#include "SubTexture2D.h"
//
//class GameObject;
//
//
//class SpriteComponent : public Component
//{
//public:
//
//	COMPONENT_STATIC_TYPE(Sprite_Type);
//
//	//If not a subtexture, pass min and max as nullptr
//	SpriteComponent(bool usingSubtexture, Texture2D& texture, const glm::vec2& min, const glm::vec2& max) {
//		SetType(Component::Types::Sprite_Type);
//		SetCategory(Component::Categories::Graphics_Category);
//
//		//Decides if the texure needs to be processed into subtextures 
//		if (usingSubtexture)
//		{
//			_subTexture = new SubTexture2D(&texture, min, max);
//			_texture = _subTexture->CreateFromTexCoords 
//
//		}
//		else
//		{
//			_texture = &texture;
//		}
//		isSubtexture = usingSubtexture;
//	};
//	SpriteComponent(GameObject* parentObject);
//
//	//Class Functionality
//	static void CreateFromTexCoords(Texture2D* texture, const glm::vec2& coords, const glm::vec2& spriteSize);
//
//
//	//Getters
//	//const glm::vec2* GetTexCoords()const { return _texCoords; }
//	//const Texture2D* GetTexture() const { return _texture; }
//	GameObject* GetGameObject() {
//		return _parentObject;
//	}
//	void OnStart() override;
//	void OnUpdate() override;
//	void OnEnd() override;
//	GameObject* _parentObject;
//	void SetGameObject(GameObject* newParent) {
//		_parentObject = newParent;
//	}
//
//	// Inherited via ISerializable
//	virtual bool SaveState(IStream& stream) const override {
//		Component::SaveState(stream);
//
//		return true;
//	}
//	virtual bool LoadState(IStream& stream) override {
//		Component::LoadState(stream);
//
//		return true;
//	}
//	// Inherited via Component
//	virtual void DrawEditorUI() override;
//
//private:
//	Texture2D* _texture;
//	SubTexture2D* _subTexture;
//	GLuint _ID;
//
//	////Processes the required spacing and division needed to create subtextures
//	////from spritesheets (individual small textures from large multi texture image)
//	//void ProcessTexCoords(Texture2D& texture, const glm::vec2& min, const glm::vec2& max);
//
//	//SubTexture Variables (sprites from spritesheets
//	bool isSubtexture;
//	//glm::vec2 _texCoords[4];
//
//};