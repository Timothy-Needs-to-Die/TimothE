#include "pch.h"

#include "Application.h"

void main() {
	Application* game = new Application();
	game->Init(true);
	game->GameLoop();

	delete game;
	game = nullptr;
}