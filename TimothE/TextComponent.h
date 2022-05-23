#pragma once

#include "Font.h"
#include "Core/Graphics/Shader.h"
#include "GameObject.h"
#include "Component.h"
#include "Console.h"

enum TextAlignment {
	LEFT = 0,
	CENTER,
	RIGHT
};

class TextComponent : public Component
{
public:

	COMPONENT_STATIC_TYPE(Text_Type);

	TextComponent(GameObject* parentObject);
	~TextComponent();

	void OnStart();
	void OnEnd();
	void OnUpdate();

	void SetFont(string font) { _font = ResourceManager::GetFont(font); }
	void SetText(string text) { _text = text; }

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
public:
	Font* _font;
	std::string _text;
	float _scale;
	glm::vec3 _color;
	TextAlignment _alignment;
private:
	std::string _UID;
	Shader* _shader;
	GameObject* _parentObject;

	bool _hasInit = false;
};
