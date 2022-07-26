#include "pch.h"

#include "Application.h"

void main() {
	std::shared_ptr<Application> game = std::make_shared<Application>();

	game->Init();
	game->GameLoop();
}