#pragma once
#include "Component.h"

class SpriteComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(Texture_Type);
	//COMPONENT_STATIC_Catagory(Graphics_Category);

	SpriteComponent(GameObject* parent);
	~SpriteComponent();
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	virtual void DrawEditorUI() override;
	bool* _editorIsEnabled;


	virtual bool SaveState(IStream& stream) const override {
		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		return true;
	}
private:
};

