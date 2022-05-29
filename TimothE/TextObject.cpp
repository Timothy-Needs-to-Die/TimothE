#include "pch.h"
#include "TextObject.h"
#include "TextComponent.h"

TextObject::TextObject(std::string text, std::string font, std::string name, std::string tag)
	: GameObject(name, tag)
{
	_pText = AddComponent(new TextComponent(this));
	_pText->SetText(text);
	_pText->SetFont(font);
}
