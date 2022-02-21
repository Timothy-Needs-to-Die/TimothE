#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "Sprite.h"

class SpriteComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(SpriteType)

	SpriteComponent(GameObject* parent);
	~SpriteComponent();
	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnEnd() override;
	virtual void DrawEditorUI() override;
	bool* _editorIsEnabled;

	void SetPosition(glm::vec2);
	glm::vec2 GetPosition() { return glm::vec2(_mPosX, _mPosY); };
	void SetSpriteSheetScale(glm::vec2);
	glm::vec2 GetSpriteSheetScale() { return glm::vec2(_mSheetWidth, _mSheetHeight); };
	void SetSpriteScale(glm::vec2);
	glm::vec2 GetSpriteScale() { return glm::vec2(_mSpriteWidth, _mSpriteHeight); };
	void SetSprite(Sprite* sprite);
	Sprite* GetSprite() { return _pSprite; };

	void SetUVCoords();
	void SetUVCoords(glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight);

	virtual bool SaveState(IStream& stream) const override {
		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		return true;
	}
private:
	Sprite* _pSprite;

	float _mPosX, _mPosY;
	float _mSheetWidth, _mSheetHeight;
	int _mSpriteWidth, _mSpriteHeight;
	//Texture2D* _pSprite;
	glm::vec2* _pUVSpriteCoords;
};

