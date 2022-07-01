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

	//Loads the tilemap
	void LoadTileMap();

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

	/// <summary>
	//Returns the entirety of the tileArr (Large object. Use with caution)
	/// </summary>
	std::vector<std::vector<std::vector<TileData>>> GetAllTiles() const {
		return _tileArr;
	}
	
	/// <summary>
	//Returns a vector of TileData of the specified layer
	/// </summary>
	std::vector<std::vector<TileData>> GetAllTilesInLayer(int layer) const {
		//Range check the passed in layer
		if (layer < 0) layer = 0;
		if (layer >= _numLayers) layer = _numLayers - 1;

		return _tileArr[layer];
	}


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
	bool CollidableAtPosition(int index) const;
	bool CollidableAtIndexXY(int x, int y);

	void UpdateLightLevelAtPosition(glm::vec2 pos, int lightLevel);
	void UpdateRenderInfo();

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
	void SetCollidableAtPosition(glm::vec2 pos, bool val);
	int GetTileIndexFromPosition(glm::vec2 pos);

	/// <summary>
	/// Set a broad light level for every tile in the tile map (Intensive, Use carefully!).
	/// </summary>
	/// <param name="level"> Applicable light level for tiles.</param>
	void SetAllTilesLightLevel(int level);


	void GenerateTileMap(int noOfRooms = 10, int width = 64, int height = 64, int seed = -1);

	int GetLightLevelAtPosition(glm::vec2 pos);
	

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

	//X and Y Gap between tiles 1 unit / tiles per unit
	float _gapBetweenTiles;

	//The current tile that the mouse is hovering over
	glm::vec2 _currentTile;
	
	//The index of the current tile that the mouse is hovering over
	int _currentTileIndex;

	//vector of vectors which holds the tiles on each layer. _tileArr[0][5] refers to tile five of the first layer. 
	std::vector<std::vector<std::vector<TileData>>> _tileArr;
	std::vector<TileData*> _animatedTileArr;

	float _mapAnimationDuration = 0.25f;
	float _mapAnimationTimer = 0.0f;

	bool** _collidableTileArray;

	int* _lightLevelArray;

	//How many tiles are there per unit in the X and Y axis
	int _tilesPerUnit = 4;

	//The name of the tilemap is used to save and load the map
	std::string _name;

	std::vector<struct RendererData> _tilemapRendererData;
};

