#include <vector>
#include <string>
#include <glm.hpp>

class TileMap
{
public:
	TileMap();
	~TileMap();



private:
	//VAO Vertex Arraty
	glm::vec2 mapSize;
	glm::vec2 tileSize;
	std::string textureName;

};

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}