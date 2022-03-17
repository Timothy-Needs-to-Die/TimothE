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

	unsigned int currentLayer = 0;
	unsigned int _tileIndex = -1; //-1 if no tile is present upon click
};

class TileMapEditor
{
public:

	static void EnableEditor();
	static void Update(TileMap* pTilemap);

private:
	
	static bool _isActive;

	//This bool represents if the tile data has been recieved from the relating tile map. If it has not, the data should be aqquired. 
	static bool _hasTileData;
	static std::string _mapName;
	static std::string _textureName;
	static glm::vec2 _mapSizeInScreenUnits;
	static glm::vec2 _tileSize;
	static std::string _name;

	static SelectedTile _selectedTile;
	
	static void AcquireData(TileMap* pTilemap);
	static void CreateTileMap(TileMap* pTilemap);
	static void SaveTileMap(const TileMap& map, const std::vector<bool>& collisionInfo);

};

