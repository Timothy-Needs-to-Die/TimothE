#pragma once
#include "pch.h"

struct TileData {
	int xIndex;
	int yIndex;
	int layer;

	bool collidable;
	float size;
	float colXPos;
	float colYPos;

	glm::vec2* uvCoords;
};