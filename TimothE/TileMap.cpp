#include "TileMap.h"

TileMap::TileMap()
{
	_tiles.resize(16 * 16);
	//CreateTileMap();
}

TileMap::~TileMap()
{
}

void TileMap::CreateTileMap() {
	using nlohmann::json;
	std::ifstream file(_tileMapFile);
	if (!file) {
		std::cout << "Unable to open file" << _tileMapFile << std::endl;
		return;
	}
	json root; 
	file >> root;

	_tileSize.x = root["TILE_WIDTH"];
	_tileSize.y = root["TILE_HEIGHT"];

	_mapSize.x = root["WIDTH"];
	_mapSize.y = root["HEIGHT"];

	const auto& layers = root["LAYERS"];
	_textureName = root["TEXTURE_NAME"];
	auto texturePtr = ResourceManager::GetTexture(_textureName);

	if (!texturePtr)
	{
		std::cout << "Error: Tilemap Texture not found" << std::endl;
		return;
	}

	for (const auto& layer : layers)
	{
		const auto& layerData = layer["DATA"];

		//VAO Vertex array vertices
	}

	//TODO: Abstract this out map width * map height


}

void TileMap::CreateNewLayer()
{
}

void TileMap::DeleteAllLayers()
{
}

void TileMap::AddTileAt(unsigned int layer, unsigned int i, unsigned int j, unsigned int index)
{
	auto texturePointer = ResourceManager::GetTexture(_textureName);
	if (!texturePointer)
	{
		std::cout << "Unable to create tilemap: Texture was not found in resouce manager" << std::endl;
	}

	//int x = (texturePointer->GetWidth() / _tileSize.x);
	//int y = (texturePointer->GetHeight() / _tileSize.y);
	//
	//int tu = index % x;
	//int tv;
	//
	//if (y % 2 == 0)
	//	tv = index / y;
	//else
	//	tv = index / (y - 1);


	TileData newTile;
	newTile.xIndex = i;
	newTile.yIndex = j;
	newTile.layer = layer;

	glm::vec2 worldPos;

	//TODO: abstract this out
	int tileSize = 32;
	int mapWidth = 16;
	int mapHeight = 16;

	int divisibleX = index / mapWidth;

	int tI = index - (mapWidth * divisibleX);

	worldPos.x = (float)tI * (float)tileSize;
	worldPos.y = (float)divisibleX * tileSize;

	_tiles[index] = newTile;

	std::cout << "Tile placed at: (X: " << worldPos.x << " Y: " << worldPos.y << ")" << std::endl;



}

int TileMap::GetTileWidth() const
{
	return 0;
}

int TileMap::GetTileHeight() const
{
	return 0;
}

std::string TileMap::GetTextureName() const
{
	return std::string();
}

std::string TileMap::GetName() const
{
	return std::string();
}

void TileMap::FillLayer(unsigned int layer, int tileIndex)
{
}

glm::vec2 TileMap::GetTileSize() const
{
	return glm::vec2();
}

void TileMap::SetTileSize(glm::vec2 tileSize)
{
}

void TileMap::SetPosition(float x, float y)
{
}

void TileMap::SetTileMapSize(glm::vec2 mapSize)
{
}

void TileMap::SetMapName(std::string name)
{
}

void TileMap::SetTextureName(std::string name)
{
}

void TileMap::Clear()
{
}

void TileMap::RenderMap() const
{
}



unsigned int TileMap::GetLayerCount()
{
	return 0;
}
