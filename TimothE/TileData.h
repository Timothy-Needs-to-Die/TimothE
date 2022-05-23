#pragma once
#include "pch.h"
#include "SpriteSheet.h"
#include "Sprite.h"

struct TileData {
	int texIndex;
	int layer;

	bool collidable;
	float size;
	float colXPos;
	float colYPos;

	Sprite* _pSprite;
	SpriteSheet* _pSpritesheet;

	int lightLevel = 0;
};