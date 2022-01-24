#include <vector>
#include <string>
#include <glm.hpp>

class TileMap
{
public:
	TileMap();
	~TileMap();

	void SetTileSize(glm::vec2 tileSize);
	void SetPosition(float x, float y);
	void SetTileMapSize(glm::vec2 mapSize);
	void SetMapName(std::string name);
	void SetTextureName(std::string name);
	void CreateNewLayer();
	void FillLayer(unsigned int layer, int tileIndex);
	void DeleteAllLayers();
	void Clear();

	unsigned int GetLayerCount();

private:
	//VAO Vertex Array
	glm::vec2 mapSize;
	glm::vec2 tileSize;
	std::string textureName;
	std::string _tileMapFile;


};

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}