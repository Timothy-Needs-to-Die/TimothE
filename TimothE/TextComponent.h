#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <iostream>
#include <glm/glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Shader.h"
#include "Component.h"

struct Character
{
	unsigned int _textureID; // ID handle of the glyph texture
	glm::ivec2 _size;		// Size of glyph
	glm::ivec2 _bearing;		// Offset from baseline to left/top of glyph
	unsigned int _advance;	// Offset to advance to next glyph
};


class TextComponent
{
public:
	TextComponent(std::string font);
	~TextComponent();

	void SetFont(std::string font) { _font = font; }
	void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);

private:
	unsigned int _VAO, _VBO;
	std::map<char, Character> _characters;
	std::string _font;


	void OnStart();
	void OnEnd();
};

