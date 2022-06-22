#pragma once
#include "pch.h"
#include "SpriteSheet.h"
#include "Sprite.h"

struct TileData {
	bool animated = false;
	std::vector<unsigned int> animatedTileIDs;
	unsigned int animationIndex = 0;

	unsigned int texIndex;
	unsigned int layer;

	float size;

	glm::vec2 pos;

	Sprite* _pSprite;
	SpriteSheet* _pSpritesheet;
};