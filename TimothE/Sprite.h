#pragma once
#include "pch.h"
#include "Texture2D.h"

class Sprite
{
public:
	Sprite(Texture2D* texture, glm::vec2* pTexCoords = nullptr);
	Sprite() = default;
	~Sprite();

	glm::vec2* GetTexCoords() const { return _pTexCoords; }
	Texture2D* GetTexture() const { return _pTexture; }

private:
	glm::vec2* _pTexCoords;
	Texture2D* _pTexture;

};

