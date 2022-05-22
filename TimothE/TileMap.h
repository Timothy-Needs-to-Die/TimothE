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

	//Sets the new spritesheet for this tilemap. 
	void SetSpriteSheet(SpriteSheet* spritesheet) {
		_pSpritesheet = spritesheet;
		_tileSize = { _pSpritesheet->GetSpriteWidth(), _pSpritesheet->GetSpriteHeight() };
		_spritemapResolution = { _pSpritesheet->GetPixelWidth(), _pSpritesheet->GetPixelHeight() };
	}

	void LoadTileMap();

	//Returns the spritesheet for this tilemap
	SpriteSheet* GetSpriteSheet() { return _pSpritesheet; }

	//Adds a tile to a specified layer with a specified x and y index for the sprite, oritented around a camera and taked in a flag for collisions
	void AddTileAt(unsigned int layer, unsigned int uvX, unsigned int uvY, Camera* cam, bool shouldCollide = false);

	//Fills a specified layer with a texture at uvX and uvY coordinates
	void FillLayer(unsigned int layer, int uvX, int uvY);

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
		_tileArr[0].resize(elementSize);
		_tileArr[1].resize(elementSize);
		_tileArr[2].resize(elementSize);

		_mapSizeInUnits = glm::vec2(_mapInTiles.x / _tilesPerUnit, _mapInTiles.y / _tilesPerUnit);
	}

	std::vector<TileData> GetTiles() { return _tileArr[3]; }

	int GetTilesPerUnit() const {
		return _tilesPerUnit;
	}
	
	TileData* GetTileAtWorldPos(int layer, glm::vec2 worldPos);
	
	void ClearLayer(int layer);
	
	glm::vec2 ConvertWorldToScreen(glm::vec2 inPos) {
		glm::vec2 outPos{ inPos.x / 1920.0f, inPos.y / 1080.0f };
		return outPos;
	}

	void RenderMap(Camera* cam);

	bool CollidableAtPosition(const int x, const int y) const;
	bool CollidableAtPosition(const int index);
	bool CollidableAtPosition(glm::vec2 worldPos) ;


private:
	int _numLayers = 3;

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

	//The spritesheet for this spritemap
	SpriteSheet* _pSpritesheet = nullptr;

	//Array/Vector which holds the tiles. //TODO: Make this not magic and link to the _numLayers variable
	std::vector<TileData> _tileArr[3];

	//How many tiles are there per unit in the X and Y axis
	int _tilesPerUnit = 4;

	std::string _name;
};

