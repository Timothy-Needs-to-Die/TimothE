#pragma once
#include "pch.h"

struct Quad {
	Quad(glm::vec2 pos = glm::vec2(0.0f), glm::vec2 size = glm::vec2(0.25f), float rot = 0.0f) {
		position = pos;
		this->size = size;
		rotation = rot;
	}

	glm::vec2 position;
	glm::vec2 size;
	float rotation;
};

