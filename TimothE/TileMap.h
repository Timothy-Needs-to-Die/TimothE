#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include <nlohmann/json.hpp>

#include "Camera.h"
#include "ResourceManager.h"
#include "TileData.h"




class TileMap
{
public:
	TileMap(std::string name);
	~TileMap();

	void SaveTilemap();
	void ClearAllLayers();
	void UpdateLogic(Camera* cam);

	void LoadTileMap();


	//Adds a tile to a specified layer with a specified x and y index for the sprite, oritented around a camera and taked in a flag for collisions
	void AddTileAt(unsigned int layer, unsigned int uvX, unsigned int uvY, Camera* cam, SpriteSheet* sp, bool shouldCollide = false);

	//Fills a specified layer with a texture at uvX and uvY coordinates
	void FillLayer(unsigned int layer, int uvX, int uvY, SpriteSheet* sp);

	//Gets the size of a tile in units. (e.g. 0.25 x 0.25)

	glm::vec2 GetTileSize() const
	{
		return _tileSize;
	}

	//Converts the mouse position to a tile, takes in a camera to base the calculations around
	glm::vec2 MousePosToTile(Camera* cam);

	//Sets the size of the tilemap in tiles. e.g a 256 x 140 tile map.
	void SetTileMapSize(glm::vec2 mapSize)
	{
		_mapInTiles = mapSize;
		int elementSize = _mapInTiles.x * _mapInTiles.y;
		//_tileArr[0].resize(elementSize);
		//_tileArr[1].resize(elementSize);
		//_tileArr[2].resize(elementSize);

		for (int i = 0; i < _tileArr.size(); i++) {
			_tileArr[i].resize(elementSize);
		}

		_mapSizeInUnits = glm::vec2(_mapInTiles.x / _tilesPerUnit, _mapInTiles.y / _tilesPerUnit);
	}

	glm::vec2 GetTileMapDimensions() const {
		return _mapInTiles;
	}


	int GetTilesPerUnit() const {
		return _tilesPerUnit;
	}

	glm::vec2 GetMapSize() const {
		return _mapSizeInUnits;
	}
	
	TileData* GetTileAtWorldPos(int layer, glm::vec2 worldPos);

	TileData GetTileAtIndex(int layer, int index) { return _tileArr[layer][index]; }

	std::vector<std::vector<TileData>> GetAllTiles() const {
		return _tileArr;
	}
	
	std::vector<TileData> GetAllTilesInLayer(int layer) const {
		return _tileArr[layer];
	}
	
	void ClearLayer(int layer);
	
	glm::vec2 ConvertWorldToScreen(glm::vec2 inPos) {
		glm::vec2 outPos{ inPos.x / 1920.0f, inPos.y / 1080.0f };
		return outPos;
	}

	void RenderMap(Camera* cam);

	bool CollidableAtPosition(const int x, const int y) const;
	bool CollidableAtPosition(const int index);
	bool CollidableAtPosition(glm::vec2 worldPos) ;

	void SetCollidableAtLayer(int layer, glm::vec2 pos, bool val);
	int GetTileIndexFromPosition(glm::vec2 pos);

private:
	int _numLayers = 6;

	//How large the map is in units. e.g. 32 meters by 20 meters. 
	glm::vec2 _mapSizeInUnits;

	//How large each of the tiles are in pixel size
	glm::vec2 _tileSize;

	//How large the map is in tiles. mapSizeInScreenUnits * tilesPerUnit
	glm::vec2 _mapInTiles;

	//Resolution of the sprite map in pixels. e.g. 2560 x 1664 (20, 13 map of 128x128 pixel sprites)
	glm::vec2 _spritemapResolution;

	//X and Y Gap between tiles 1 unit / tiles per unit
	float _gapBetweenTiles;

	//The current tile that the mouse is hovering over
	glm::vec2 _currentTile;
	
	//The index of the current tile that the mouse is hovering over
	int _currentTileIndex;

	//Array/Vector which holds the tiles. //TODO: Make this not magic and link to the _numLayers variable
	std::vector<std::vector<TileData>> _tileArr;

	//How many tiles are there per unit in the X and Y axis
	int _tilesPerUnit = 4;

	std::string _name;
};

