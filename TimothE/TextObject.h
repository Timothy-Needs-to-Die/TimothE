#pragma once
#include "GameObject.h"
class TextObject : public GameObject
{
public:
	TextObject(std::string text, std::string font, std::string name, std::string tag);

	class TextComponent* GetText() const { return _pText; }

private:
	class TextComponent* _pText;

};

