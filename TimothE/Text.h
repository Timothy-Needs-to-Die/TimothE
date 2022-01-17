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
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2 Size;		// Size of glyph
	glm::ivec2 Bearing;		// Offset from baseline to left/top of glyph
	unsigned int Advance;	// Offset to advance to next glyph
};


class Text
{
private:
	std::map<char, Character> Characters;
	unsigned int VAO, VBO;
public:
	Text();
	~Text();
	int Initialise();
	void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
};

