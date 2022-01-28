#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include <nlohmann/json.hpp>

#include "Camera.h"
#include "ResourceManager.h"


struct TileData {
	int xIndex;
	int yIndex;
	int layer;

	glm::vec2* uvCoords;
};


class TileMap
{
public:
	TileMap();
	~TileMap();

	void CreateTileMap();
	void CreateNewLayer();
	void DeleteAllLayers();

	void AddTileAt(unsigned int layer, unsigned int x, unsigned int y, Camera* cam);

	//Returns the width and height of the WHOLE TILE MAP
	int GetTileWidth() const;
	int GetTileHeight() const;
	std::string GetTextureName() const;
	std::string GetName() const;
	void FillLayer(unsigned int layer, int tileIndex);

	//Returns the hight and width of the tiles themselves
	glm::vec2 GetTileSize() const;

	void SetTileSize(glm::vec2 tileSize);
	void SetPosition(float x, float y);
	void SetTileMapSize(glm::vec2 mapSize);
	void SetMapName(std::string name);
	void SetTextureName(std::string name);
	
	
	void Clear();
	
	glm::vec2 ConvertWorldToScreen(glm::vec2 inPos) {
		glm::vec2 outPos{ inPos.x / 1920.0f, inPos.y / 1080.0f };
		return outPos;
	}

	void RenderMap(Camera* cam);


private:
	//VAO Vertex Array
	glm::vec2 _mapSizeInScreenUnits;
	glm::vec2 _tileSize;
	glm::vec2 _mapDimensions;
	glm::vec2 _spritemapResolution;
	std::string _textureName;
	std::string _tileMapFile;
	float _xGapBetweenTiles;
	float _yGapBetweenTiles;

	std::vector<TileData> _tiles;

	glm::vec2* _noTcCoords;

	int _tilesPerUnit = 4;
	float _tileScale = 1.0f;


};

