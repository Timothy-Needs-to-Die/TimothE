#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "Sprite.h"

class SpriteComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(SpriteType)

	SpriteComponent(GameObject* parent, int drawOrder);
	~SpriteComponent();
	void OnStart() override;
	void OnUpdate() override;
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

	int GetDrawOrder() const { return _drawOrder; }

	void SetUVCoords();
	void SetUVCoords(glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight);

private:
	Sprite* _pSprite;

	int _drawOrder;
	float _mPosX, _mPosY;
	float _mSheetWidth, _mSheetHeight;
	int _mSpriteWidth, _mSpriteHeight;
	//Texture2D* _pSprite;
	glm::vec2* _pUVSpriteCoords;
};

