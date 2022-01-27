#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include <nlohmann/json.hpp>

#include "ResourceManager.h"


struct TileData {
	int xIndex;
	int yIndex;
	int layer;
	glm::vec2 worldPos;
};


class TileMap
{
public:
	TileMap();
	~TileMap();

	void CreateTileMap();
	void CreateNewLayer();
	void DeleteAllLayers();

	void AddTileAt(unsigned int layer, unsigned int i, unsigned int j, unsigned int index);

	//Returns the width and height of the WHOLE TILE MAP
	int GetTileWidth() const;
	int GetTileHeight() const;
	std::string GetTextureName() const;
	std::string GetName() const;
	void FillLayer(unsigned int layer, int tileIndex);

	//Returns the hight and witdh of the tiles themselves
	glm::vec2 GetTileSize() const;

	void SetTileSize(glm::vec2 tileSize);
	void SetPosition(float x, float y);
	void SetTileMapSize(glm::vec2 mapSize);
	void SetMapName(std::string name);
	void SetTextureName(std::string name);
	
	
	void Clear();
	
	void RenderMap() const;
	//const std::vector<std::vector<int>>& GetTileData() const;

	unsigned int GetLayerCount();

private:
	//VAO Vertex Array
	glm::vec2 _mapSize;
	glm::vec2 _tileSize;
	std::string _textureName;
	std::string _tileMapFile;

	std::vector<TileData> _tiles;


};

