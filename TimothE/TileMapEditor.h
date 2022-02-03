//#include <GLFW/glfw3.h>
//#include <gl/glew.h>
#include <nlohmann/json.hpp>
#include "imgui.h"
#include "TileMap.h"
#include "ResourceManager.h"
#include "Input.h"

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


	void EnableEditor();
	void DisplayEditorGUI();

	TileMapEditor();

private:
	
	bool _isActive;

	//This bool represents if the tile data has been recieved from the relating tile map. If it has not, the data should be aqquired. 
	bool _hasTileData;
	std::string _mapName;
	std::string _textureName;
	glm::vec2 _mapSizeInScreenUnits;
	glm::vec2 _tileSize;
	std::string _name;

	SelectedTile _selectedTile;

	

	void AcquireData();
	void CreateTileMap();
	void SaveTileMap(const TileMap& map, const std::vector<bool>& collisionInfo);

};

