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

	//Saves the current tilemap
	void SaveTilemap();

	//Clears all layers of the tilemap. (WARNING UNREVERSIBLE)
	void ClearAllLayers();

	//Update logic for the tilemap such as deciding which tile the mouse is over
	void UpdateLogic(Camera* cam);

	//Loads the tilemap
	void LoadTileMap();


	/// <summary>
	/// Adds a tile to the specified layer with a specified x and y coordinate on a specified spritesheet
	/// </summary>
	/// <param name="layer">The layer you want to fill</param>
	/// <param name="uvX">The X position of the sprite on the spritesheet. In whole numbers e.g sprite 4</param>
	/// <param name="uvY">The Y position of the sprite on the spritesheet. In whole numbers e.g sprite 7</param>
	/// <param name="cam">The camera that will be used to perform mouse positon calculations</param>
	/// <param name="sp">The spritesheet you want to place a tile from</param>
	/// <param name="shouldCollide">If this tile should be collidable or not</param>
	void AddTileAt(unsigned int layer, unsigned int uvX, unsigned int uvY, Camera* cam, SpriteSheet* sp, bool shouldCollide = false);

	/// <summary>
	/// Fills the desired layer with a specified x and y coordinate on a specified spritesheet
	/// </summary>
	/// <param name="layer">The layer you want to fill</param>
	/// <param name="uvX">The X position of the sprite on the spritesheet. In whole numbers e.g sprite 4</param>
	/// <param name="uvY">The Y position of the sprite on the spritesheet. In whole numbers e.g sprite 7</param>
	/// <param name="sp">The spritesheet you want to place a tile from</param>
	void FillLayer(unsigned int layer, int uvX, int uvY, SpriteSheet* sp);

	//Converts the mouse position to a tile, takes in a camera to base the calculations around
	glm::vec2 MousePosToTile(Camera* cam);

	/// <summary>
	/// Sets the size of the tilemap in tiles e.g. Pass in 64,32 if you want a 64 to tile wide 32 tile tall map.
	/// </summary>
	/// <param name="mapSize"></param>
	void SetTileMapSize(glm::vec2 mapSize);

	//Returns the dimensions of the tilemap in tile size. E.g. 64 x 32 tiles in size
	glm::vec2 GetTileMapDimensions() const {
		return _mapInTiles;
	}

	//Returns the amount of tiles per unit. Tiles per unit refers to how many tiles fit into a 1 unit wide and tall square. Defaulted to 4.
	int GetTilesPerUnit() const {
		return _tilesPerUnit;
	}

	/// Returns the size of the map in units. (Metres). A 64x32 tile map with 0.25 units per tile would be 16.0 x 8.0 units in size
	glm::vec2 GetMapSize() const {
		return _mapSizeInUnits;
	}
	
	/// <summary>
	/// Gets a tile at a specified world position on a specified layer
	/// </summary>
	/// <param name="layer">The layer the tile is on starting at 0. (Current Range 0 - 5)</param>
	/// <param name="worldPos">The world position you want to query</param>
	TileData* GetTileAtWorldPos(int layer, glm::vec2 worldPos);

	//Returns the entirety of the tileArr (Large object. Use with caution)
	std::vector<std::vector<TileData>> GetAllTiles() const {
		return _tileArr;
	}
	
	//Returns a vector of TileData of the specified layer
	std::vector<TileData> GetAllTilesInLayer(int layer) const {
		//Range check the passed in layer
		if (layer < 0) layer = 0;
		if (layer >= _numLayers) layer = _numLayers - 1;

		return _tileArr[layer];
	}

	/// <summary>
	/// Resets the tiledata of a layer
	/// </summary>
	/// <param name="layer">The layer of the tilemap you wish to clear. Starting at 0. (Current Range 0 - 5)</param>
	void ClearLayer(int layer);

	/// <summary>
	/// Renders the tilemap around a specific Camera
	/// </summary>
	/// <param name="cam">The camera you want to render from</param>
	void RenderMap(Camera* cam);

	/// <summary>
	/// Returns true if any tile on all layers at a row and column position is collidable
	/// </summary>
	/// <param name="x">The Row the tile would be on</param>
	/// <param name="y">The Column the tile is on</param>
	bool CollidableAtPosition(const int x, const int y) const;

	/// <summary>
	/// Returns true if any tile on all layers at the passed in index is collidable
	/// </summary>
	/// <param name="index">The index you want to check</param>
	bool CollidableAtPosition(const int index) const;

	/// <summary>
	/// Returns true if any tile on all layers at the passed in world position is collidable. 
	/// </summary>
	/// <param name="worldPos">The world position you want to query</param>
	bool CollidableAtPosition(glm::vec2 worldPos);
	
	/// <summary>
	/// Sets a specified tile on a specified layer to a specified collision value
	/// </summary>
	/// <param name="layer">The layer (starting at 0) you want to query. (0 - 5 Accepted range currently) </param>
	/// <param name="pos">Position of the tile in world space</param>
	/// <param name="val">Should the tile be collidable</param>
	void SetCollidableAtLayer(int layer, glm::vec2 pos, bool val);
	int GetTileIndexFromPosition(glm::vec2 pos);

	//Returns the name of the tilemap
	std::string GetName() const { return _name; }

private:
	//Controls how many layers are used in the tilemap
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

	//vector of vectors which holds the tiles on each layer. _tileArr[0][5] refers to tile five of the first layer. 
	std::vector<std::vector<TileData>> _tileArr;

	//How many tiles are there per unit in the X and Y axis
	int _tilesPerUnit = 4;

	//The name of the tilemap is used to save and load the map
	std::string _name;
};

