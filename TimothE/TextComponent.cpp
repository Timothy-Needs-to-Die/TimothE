#include "pch.h"
#include "TextComponent.h"
#include "imgui.h"
#include "Dirent.h"
#include "misc/cpp/imgui_stdlib.h"

TextComponent::TextComponent(GameObject* parentObject) : Component(parentObject)
{
	_UID = UID::GenerateUID();
	SetFont("arial.ttf");
	_text = "Enter\ntext\nhere...";
	_shader = new Shader("Resources/Shaders/txtVert.vs", "Resources/Shaders/txtFrag.fs");
	_scale = 1.0f;
	_color = { 1.0f, 1.0f, 1.0f };
	_alignment = CENTER;
	SetType(Component::Types::Text_Type);
}

TextComponent::~TextComponent()
{
}

void TextComponent::OnStart()
{

}

void TextComponent::OnEnd()
{
}

void TextComponent::OnUpdate()
{

}


void TextComponent::Render()
{
	RenderText(*_shader, _text, _pOwner->GetTransform()->GetPosition().x, _pOwner->GetTransform()->GetPosition().y, _scale, _color); // pass in _alignment
}

void TextComponent::RenderText(Shader& s, std::string text, float x = 0.0f, float y = 0.0f, float _tileScale = 1.0f, glm::vec3 color = { 1.0f, 1.0f, 1.0f })
{
	if (_font != nullptr)
		_font->RenderText(s, text, x, y, _tileScale, color);
}