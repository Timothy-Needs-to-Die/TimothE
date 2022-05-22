//#include <GLFW/glfw3.h>
//#include <gl/glew.h>
#include <nlohmann/json.hpp>
#include "imgui.h"
#include "TileMap.h"
#include "ResourceManager.h"
#include "Input.h"
#include "CameraManager.h"

#include "Texture2D.h"
#include <string>
//#include "glm.hpp"

#pragma once

struct SelectedTile
{
	//Sprite sprite;
	int tileX;
	int tileY;
};

class TileMapEditor
{
public:

	static void Update(TileMap* pTilemap);

private:
	//Name of the spritesheet used for this tilemap.
	static std::string _spritesheetName;

	//Size of the map in tiles.
	static glm::vec2 _mapSizeInUnits;

	//Current layer we are editing
	static int _currentLayer;

	//Should the tile we are placing down be collidable
	static bool _collidableToggle;

	//The tile we want to place down.
	static SelectedTile _selectedTile;
	
	static void EditorUI(TileMap* pTilemap);
};

