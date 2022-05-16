#include "Font.h"
#include "Core/Graphics/OpenGLError.h"
#include "Core.h"

Font::Font(std::string font)
{
	_name = font;

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		TIM_LOG_ERROR("Failed to initialize Freetype");
		return;
	}
	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
	{
		TIM_LOG_ERROR("Failed to load Font");
		return;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		TIM_LOG_ERROR("Failed to load Glyph");
		return;
	}

	// disable byte-alignment restriction
	GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

	for (unsigned char c = 0; c < 128; c++)
	{
		// load character gylph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			TIM_LOG_ERROR("Failed to load Glyph");
			continue;
		}
		// generate texture
		unsigned int texture;
		GLCall(glGenTextures(1, &texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture));
		GLCall(glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		));
		// set texture options
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		// now store character for later use
		TextCharacter character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		_characters.insert(std::pair<char, TextCharacter>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GLCall(glGenVertexArrays(1, &_VAO));
	GLCall(glGenBuffers(1, &_VBO));
	GLCall(glBindVertexArray(_VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

Font::~Font()
{
}

void Font::RenderText(Shader& s, std::string text, float x = 0.0f, float y = 0.0f, float scale = 1.0f, glm::vec3 color = { 1.0f, 1.0f, 1.0f })
{
	if (_VBO == 0) {
		TIM_LOG_ERROR("VBO associated with font: " << _name << " is 0");
		return;
	}
	if (_VAO == 0) {
		TIM_LOG_ERROR("VAO associated with font: " << _name << " is 0");
		return;
	}

	// activate corresponding render state
	s.BindShader();
	GLCall(glUniform3f(glGetUniformLocation(s.GetProgramID(), "textColor"), color.x, color.y, color.z));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindVertexArray(_VAO));

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	s.SetMat4("projection", projection);

	int newline = 0;
	float newlineXPos = x;
	float newlinePadding = (this->_characters['H']._bearing.y + this->_characters['H']._bearing.y / 3);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		TextCharacter ch = _characters[*c];
		if (*c == '\n')
		{
			newline++;
			x = newlineXPos;
			continue;
		}
		float xpos = x + ch._bearing.x * scale;
		float ypos = y - (ch._size.y - ch._bearing.y) * scale - ((newlinePadding * scale) * newline);

		float w = ch._size.x * scale;
		float h = ch._size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		GLCall(glBindTexture(GL_TEXTURE_2D, ch._textureID));
		// update content of VBO memory
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, _VBO));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		// render quad
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch._advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	GLCall(glBindVertexArray(0));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}