#pragma once
#include "pch.h"

struct Quad {
	Quad(glm::vec2 pos = glm::vec2(0.0f), glm::vec2 size = glm::vec2(5.0f)) {
		position = pos;
		this->size = size;
	}

	glm::vec2 position;
	glm::vec2 size;
};

