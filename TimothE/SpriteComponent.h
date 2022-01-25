#pragma once
#include "Component.h"
#include "Texture2D.h"

class SpriteComponent : public Component
{
public:

	SpriteComponent(GameObject* parent);
	~SpriteComponent();
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	virtual void DrawEditorUI() override;
	bool* _editorIsEnabled;

	void SetPosition(glm::vec2);
	glm::vec2 GetPosition();
	void SetSpriteSheetPosition(glm::vec2);
	glm::vec2 GetSpriteSheetPosition();
	void SetSprite(Texture2D* sprite);
	Texture2D* GetSprite();


	virtual bool SaveState(IStream& stream) const override {
		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		return true;
	}
private:
	float _mPosX;
	float _mPosY;
	int _mSpriteSheetPosX;
	int _mSpriteSheetPosY;
	Texture2D* _pSprite;
};

