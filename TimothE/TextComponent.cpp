#include "pch.h"
#include "TextComponent.h"
#include "imgui.h"
#include "Dirent.h"
#include "misc/cpp/imgui_stdlib.h"

TextComponent::TextComponent(GameObject* parentObject) : Component()
{
	_UID = UID::GenerateUID();
	SetFont(ResourceManager::GetFont("arial"));
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

void TextComponent::RenderText(Shader& s, std::string text, float x = 0.0f, float y = 0.0f, float _tileScale = 1.0f, glm::vec3 color = { 1.0f, 1.0f, 1.0f })
{
	//_font->RenderText(s, text, x, y, _tileScale, color);
}
