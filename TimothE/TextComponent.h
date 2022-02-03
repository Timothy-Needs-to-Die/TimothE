#pragma once

#include "Font.h"
#include "Shader.h"
#include "GameObject.h"
#include "Component.h"


class TextComponent : public Component
{
public:

	COMPONENT_STATIC_TYPE(Text_Type);

	TextComponent(GameObject* parentObject);
	~TextComponent();

	void OnStart();
	void OnEnd();
	void OnUpdate(float deltaTime);

	void SetFont(std::string font);

	void GetFontsInFile();

	void LoadFont();
	void RenderText(Shader& s, std::string text, float x, float y, float _tileScale, glm::vec3 color);

	void SetGameObject(GameObject* newparent) {
		_parentObject = newparent;
	}
	// Getter
	GameObject* GetGameObject() {
		return _parentObject;
	}

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		return true;
	}
	// Inherited via Component
	virtual void DrawEditorUI() override;
private:
	std::string _UID;

	Font* _font;
	std::vector<std::string> _fonts;
	std::string _text;
	Shader* _shader;
	float _scale;
	glm::vec3 _color;
	GameObject* _parentObject;

	bool _hasInit = false;
};
