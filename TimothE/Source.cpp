#include <gl/glew.h>
#include <GLFW/glfw3.h>


#include<iostream>

#include "Application.h"

void main() {
	Application* game = new Application();
	game->Init(true);
	game->GameLoop();

	delete game;
	game = nullptr;
}