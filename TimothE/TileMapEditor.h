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
	static std::string _mapName;
	static std::string _spritesheetName;
	static glm::vec2 _mapSizeInScreenUnits;
	static glm::vec2 _tileSize;
	static std::string _name;
	static int _currentLayer;
	static bool _collidableToggle;

	static SelectedTile _selectedTile;
	
	static void CreateTileMap(TileMap* pTilemap);
	static void SaveTileMap(const TileMap& map);

};

