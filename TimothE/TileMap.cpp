#include "TileMap.h"
#include "Renderer2D.h"

//TODO: Size details
TileMap::TileMap()
{
	_mapSize = glm::vec2(16.0f, 16.0f);
	_tileSize = glm::vec2(128.0f);
	_spritemapSize = glm::vec2(2560.0f, 1664.0f);
	_tiles.resize(_mapSize.x * _mapSize.y);

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

void TileMap::AddTileAt(unsigned int layer, unsigned int x, unsigned int y, unsigned int index)
{
	//auto texturePointer = ResourceManager::GetTexture(_textureName);
	//if (!texturePointer)
	//{
	//	std::cout << "Unable to create tilemap: Texture was not found in resouce manager" << std::endl;
	//}

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
	newTile.xIndex = x;
	newTile.yIndex = y;
	newTile.layer = layer;

	glm::vec2 worldPos;

	int divisibleX = index / _mapSize.x;

	int tI = index - (_mapSize.x * divisibleX);

	worldPos.x = (float)tI * (float) _tileSize.x;
	worldPos.y = (float)divisibleX * _tileSize.y;

	newTile.uvCoords = new glm::vec2[4];
	newTile.uvCoords[0] = glm::vec2((x * _tileSize.x) / _spritemapSize.x, (y * _tileSize.y) / _spritemapSize.y);
	newTile.uvCoords[1] = glm::vec2(((x + 1) * _tileSize.x) / _spritemapSize.x, (y * _tileSize.y) / _spritemapSize.y);
	newTile.uvCoords[2] = glm::vec2(((x + 1) * _tileSize.x) / _spritemapSize.x, ((y + 1) * _tileSize.y) / _spritemapSize.y);
	newTile.uvCoords[3] = glm::vec2((x * _tileSize.x) / _spritemapSize.x, ((y + 1) * _tileSize.y) / _spritemapSize.y);

	newTile.worldPos = worldPos;

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

void TileMap::RenderMap(Camera* cam)
{
	Renderer2D::BeginRender(cam);

	for (auto& t : _tiles) {
		if (t.uvCoords != nullptr) {
		Renderer2D::DrawQuad(ConvertWorldToScreen(t.worldPos), { 0.5f, 0.5f }, ResourceManager::GetTexture("spritesheet"), t.uvCoords);

		}
	}

	Renderer2D::EndRender();
}