#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <iostream>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Core/Graphics/Shader.h"
#include "Core.h"

struct TextCharacter
{
	unsigned int _textureID; // ID handle of the glyph texture
	glm::ivec2 _size;		// Size of glyph
	glm::ivec2 _bearing;		// Offset from baseline to left/top of glyph
	unsigned int _advance;	// Offset to advance to next glyph
};

class Font
{
private:
	unsigned int _VAO;// = 0;
	unsigned int _VBO;// = 0;
	std::string _name;
	std::map<char, TextCharacter> _characters;

public:
	Font(std::string font);
	~Font();

	void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
};
