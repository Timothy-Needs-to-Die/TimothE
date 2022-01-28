#include "TileMap.h"
#include "Renderer2D.h"

//TODO: Size details
TileMap::TileMap()
{
	//TODO: Add a system to change how many tiles per unit


	_mapDimensions = { 256.0f, 256.0f };
	_mapSizeInScreenUnits = glm::vec2(_mapDimensions.x / _tilesPerUnit, _mapDimensions.y / _tilesPerUnit);
	_tileSize = glm::vec2(128.0f);
	_spritemapResolution = glm::vec2(2560.0f, 1664.0f);
	_tiles.resize(_mapDimensions.x * _mapDimensions.y);

	_xGapBetweenTiles = 1.0f / _tilesPerUnit;
	_yGapBetweenTiles = 1.0f / _tilesPerUnit;

	//CreateTileMap();

	_tileScale = 1.0f / _tilesPerUnit;


	_noTcCoords = new glm::vec2[4];
	_noTcCoords[0] = glm::vec2((0 * _tileSize.x) / _spritemapResolution.x, (0 * _tileSize.y) / _spritemapResolution.y);
	_noTcCoords[1] = glm::vec2(((0 + 1) * _tileSize.x) / _spritemapResolution.x, (0 * _tileSize.y) / _spritemapResolution.y);
	_noTcCoords[2] = glm::vec2(((0 + 1) * _tileSize.x) / _spritemapResolution.x, ((0 + 1) * _tileSize.y) / _spritemapResolution.y);
	_noTcCoords[3] = glm::vec2((0 * _tileSize.x) / _spritemapResolution.x, ((0 + 1) * _tileSize.y) / _spritemapResolution.y);

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

	_mapSizeInScreenUnits.x = root["WIDTH"];
	_mapSizeInScreenUnits.y = root["HEIGHT"];

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

void TileMap::AddTileAt(unsigned int layer, unsigned int x, unsigned int y, Camera* cam)
{
	glm::vec2 mousePos = Input::GetEditorMousePos();
	mousePos.x /= (960.0f / 2.0f);
	mousePos.y /= (520.0f / 2.0f);

	glm::vec2 camPos = cam->Position();

	if (camPos.x < 0.0f)
	{
		camPos.x = 0.0f;
		mousePos.x = 0.0f;
	}
	else if (camPos.x > _mapSizeInScreenUnits.x) {
		camPos.x = _mapSizeInScreenUnits.x;
		mousePos.x = _mapSizeInScreenUnits.x;
	}

	if (camPos.y < 0.0f) {
		camPos.y = 0.0f;
		mousePos.y = 0.0f;
	}
	else if (camPos.y > _mapSizeInScreenUnits.y) {
		camPos.y = _mapSizeInScreenUnits.y;
		mousePos.y = _mapSizeInScreenUnits.y;
	}
	//if (camPos.x > 1.7f) {
	//	camPos.x -= 1.7f;
	//
	//}
	//if (camPos.y > 1.0f) {
	//	camPos.y -= 1.0f;
	//}

	if (mousePos.x < 0.5f) {
		mousePos.x = (camPos.x / 2.0f) - mousePos.x;
	}
	else {
		mousePos.x = (camPos.x / 2.0f) + mousePos.x;
	}

	if (mousePos.y < 0.5f) {
		mousePos.y = (camPos.y / 2.0f) + mousePos.y;
	}
	else {
		mousePos.y = (camPos.y / 2.0f) - mousePos.y;
	}

	std::cout << "Mouse Position: " << mousePos.x << ", " << mousePos.y << std::endl;
	std::cout << "Camera Position: " << camPos.x << ", " << camPos.y << std::endl;

	glm::vec2 worldPos = mousePos;

	int index = (int)(worldPos.y * _tilesPerUnit) * (_mapDimensions.y) + (int)(worldPos.x * _tilesPerUnit);

	TileData newTile;
	newTile.xIndex = x;
	newTile.yIndex = y;
	newTile.layer = layer;
	newTile.uvCoords = new glm::vec2[4];
	newTile.uvCoords[0] = glm::vec2((x * _tileSize.x) / _spritemapResolution.x, (y * _tileSize.y) / _spritemapResolution.y);
	newTile.uvCoords[1] = glm::vec2(((x + 1) * _tileSize.x) / _spritemapResolution.x, (y * _tileSize.y) / _spritemapResolution.y);
	newTile.uvCoords[2] = glm::vec2(((x + 1) * _tileSize.x) / _spritemapResolution.x, ((y + 1) * _tileSize.y) / _spritemapResolution.y);
	newTile.uvCoords[3] = glm::vec2((x * _tileSize.x) / _spritemapResolution.x, ((y + 1) * _tileSize.y) / _spritemapResolution.y);
	newTile.worldPos = worldPos;

	std::cout << "Index: " << index << std::endl;

	_tiles[index] = newTile;

	std::cout << "World Position: (X: " << worldPos.x << " Y: " << worldPos.y << ")" << std::endl;
	//glm::vec2 screenPos = ConvertWorldToScreen(worldPos);
	//std::cout << "In Screen space: (X: " << screenPos.x << " Y: " << screenPos.y << ")" << std::endl;
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
	glm::vec3 camPos = cam->Position();
	float extents = 4.0f;
	Renderer2D::BeginRender(cam);

	for (float y = 0; y < _mapSizeInScreenUnits.y; y+= _yGapBetweenTiles) {
		for (float x = 0; x < _mapSizeInScreenUnits.x; x += _xGapBetweenTiles) {
			if (x < camPos.x - extents || x > camPos.x + extents || y < camPos.y - extents || y > camPos.y + extents) {
				continue;
			}

			int index = (int)(y * _tilesPerUnit) * (_mapDimensions.y) + (int)(x * _tilesPerUnit);
			if (_tiles[index].uvCoords == nullptr) {
				Renderer2D::DrawQuad({ x,y }, { _tileScale, _tileScale }, ResourceManager::GetTexture("spritesheet"), _noTcCoords);
			}

			Renderer2D::DrawQuad({ x,y }, { _tileScale,_tileScale }, ResourceManager::GetTexture("spritesheet"), _tiles[index].uvCoords);
		}
	}

	Renderer2D::EndRender();
}