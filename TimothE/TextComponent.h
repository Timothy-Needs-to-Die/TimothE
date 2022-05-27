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


public:
	Font* _font;
	std::string _text;
	float _scale;
	glm::vec3 _color;
	TextAlignment _alignment;
private:
	std::string _UID;
	Shader* _shader;

	bool _hasInit = false;
};