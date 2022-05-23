#pragma once
#include "pch.h"
#include "SpriteSheet.h"
#include "Sprite.h"

struct TileData {
	int texIndex;
	int layer;

	bool collidable;
	float size;

	glm::vec2 pos;

	Sprite* _pSprite;
	SpriteSheet* _pSpritesheet;
};