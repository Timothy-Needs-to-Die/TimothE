#include "TextComponent.h"
#include "imgui.h"
#include "Dirent.h"
#include "misc/cpp/imgui_stdlib.h"

TextComponent::TextComponent(GameObject* parentObject) : Component()
{
	_UID = UID::GenerateUID();
	SetFont("arial");
	_text = "Enter text here...";
	_shader = new Shader("txtVert.vs", "txtFrag.fs");
	_scale = 1.0f;
	_color = { 1.0f, 1.0f, 1.0f };
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
		//TODO: fix the size of the array so that it's dynamic with any fonts added to the font file
		const char* items[13];
		for (int i = 0; i < _fonts.size(); i++)
		{
			items[i] = _fonts[i].c_str();
		}
		static int item_current = 0;
		if (ImGui::Combo("Font", &item_current, items, IM_ARRAYSIZE(items)))
		{
			SetFont(items[item_current]);
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

}

void TextComponent::OnEnd()
{
}

void TextComponent::OnUpdate()
{
	//_font->RenderText(*_shader, _text, _parentObject->GetTransform()->GetPosition().x, _parentObject->GetTransform()->GetPosition().y, _scale, _color);
}

void TextComponent::SetFont(std::string font)
{
	font = "fonts/" + font;
	_font = new Font(font);
	GetFontsInFile();
}

void TextComponent::GetFontsInFile() {
	std::ofstream fileStream("./fonts");
	_fonts.clear();
	DIR* directory = opendir("./fonts");
	struct dirent* dirent;
	if (directory)
	{
		while ((dirent = readdir(directory)) != NULL)
		{
			if (dirent->d_type == 32768)
			{
				_fonts.push_back(dirent->d_name);

				std::cout << "Font loaded: " << dirent->d_name << std::endl;
			}
		}
		closedir(directory);
	}
}

void TextComponent::RenderText(Shader& s, std::string text, float x = 0.0f, float y = 0.0f, float _tileScale = 1.0f, glm::vec3 color = { 1.0f, 1.0f, 1.0f })
{
	//_font->RenderText(s, text, x, y, _tileScale, color);
}
