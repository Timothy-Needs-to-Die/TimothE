#include "TextComponent.h"
#include "imgui.h"

#include "misc/cpp/imgui_stdlib.h"

TextComponent::TextComponent(GameObject* parentObject, std::string font) : Component()
{
	SetFont(font);
	_text = "Enter text here...";
	_shader = new Shader("txtVert.vs", "txtFrag.fs");
	_scale = 1.0f;
	_color = { 1.0f, 1.0f, 1.0f };
	_UID = UID::GenerateUID();
	SetType(Component::Types::Text_Type);
	SetCategory(Component::Categories::Graphics_Category);
	_parentObject = parentObject;
}

TextComponent::~TextComponent()
{
}

void TextComponent::DrawEditorUI()
{
	if (ImGui::CollapsingHeader("Text"))
	{
		ImGui::InputText("TextInput", &_text);
		const char* items[] = { "arial", "comic" };
		static int item_current = 0;
		if (ImGui::Combo("Font", &item_current, items, IM_ARRAYSIZE(items)))
		{
			SetFont(items[item_current]);
			//OnStart();
		}
		ImGui::SliderFloat("Size", &_scale, 0.01f, 5.0f, "size = %.3f");
		float col[3] = { _color.x, _color.y, _color.z };
		ImGui::ColorEdit3("Colour", col);
		{
			_color.x = col[0];
			_color.y = col[1];
			_color.z = col[2];
		}
	}
}

void TextComponent::OnStart()
{
	if (_hasInit) return;

	LoadFont();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	_hasInit = true;
}

void TextComponent::OnEnd()
{
}

void TextComponent::OnUpdate()
{
	RenderText(*_shader, _text, _parentObject->GetTransform()->GetPosition().x, _parentObject->GetTransform()->GetPosition().y, _scale, _color);
}

void TextComponent::SetFont(std::string font)
{
	_font = font;
	_fontPath = "fonts/" + font + ".ttf";
}
void TextComponent::LoadFont()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}
	FT_Face face;
	if (FT_New_Face(ft, _fontPath.c_str(), 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++)
	{
		// load character gylph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		_characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextComponent::RenderText(Shader& s, std::string text, float x = 0.0f, float y = 0.0f, float scale = 1.0f, glm::vec3 color = { 1.0f, 1.0f, 1.0f })
{
	// activate corresponding render state
	s.BindShader();
	glUniform3f(glGetUniformLocation(s.GetProgramID(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_VAO);

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	s.SetMat4("projection", projection);

	int newline = 0;
	float newlineXPos = x;
	float newlinePadding = (this->_characters['H']._bearing.y + this->_characters['H']._bearing.y / 3);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = _characters[*c];
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
		glBindTexture(GL_TEXTURE_2D, ch._textureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch._advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}