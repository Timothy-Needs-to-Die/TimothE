#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Shader.h"
#include "GameObject.h"
#include "Component.h"

struct Character
{
	unsigned int _textureID; // ID handle of the glyph texture
	glm::ivec2 _size;		// Size of glyph
	glm::ivec2 _bearing;		// Offset from baseline to left/top of glyph
	unsigned int _advance;	// Offset to advance to next glyph
};


class TextComponent : public Component
{
public:

	COMPONENT_STATIC_TYPE(Text_Type);

	TextComponent(GameObject* parentObject, std::string font);
	~TextComponent();

	void OnStart();
	void OnEnd();
	void OnUpdate();

	void SetFont(std::string font);
	void LoadFont();
	void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);

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
	unsigned int _VAO, _VBO;
	std::map<char, Character> _characters;
	std::string _font;
	std::string _fontPath;
	std::string _text;
	Shader* _shader;
	float _scale;
	glm::vec3 _color;
	GameObject* _parentObject;

	bool _hasInit = false;

};

