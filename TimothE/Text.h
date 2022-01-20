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

struct Character
{
	unsigned int _textureID; // ID handle of the glyph texture
	glm::ivec2 _size;		// Size of glyph
	glm::ivec2 _bearing;		// Offset from baseline to left/top of glyph
	unsigned int _advance;	// Offset to advance to next glyph
};


class Text
{
public:
	Text(std::string font);
	~Text();
	void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
private:
	int Initialise(std::string font);
	std::map<char, Character> _characters;
	unsigned int _VAO, _VBO;
};

