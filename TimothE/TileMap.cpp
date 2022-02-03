#include "TileMap.h"
#include "Renderer2D.h"
#include "Window.h"

//TODO: Size details
//TODO: Add a system to change how many tiles per unit
TileMap::TileMap()
{
	_mapDimensions = { 28.0f, 16.0f };
	_mapSizeInScreenUnits = glm::vec2(_mapDimensions.x / _tilesPerUnit, _mapDimensions.y / _tilesPerUnit);
	_tileSize = glm::vec2(128.0f);
	_spritemapResolution = glm::vec2(2560.0f, 1664.0f);
	_tiles.resize(_mapDimensions.x * _mapDimensions.y);

	_xGapBetweenTiles = 1.0f / _tilesPerUnit;
	_yGapBetweenTiles = 1.0f / _tilesPerUnit;

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

void TileMap::UpdateLogic(Camera* cam)
{
	_currentTile = MousePosToTile(cam);
	_currentTileIndex = _mapDimensions.x * (int)(_currentTile.y * 4) + (int)(_currentTile.x * 4);
}

void TileMap::AddTileAt(unsigned int layer, unsigned int x, unsigned int y, Camera* cam)
{
	glm::vec2 worldPos = MousePosToTile(cam);

	int index = _mapDimensions.x * (int)(worldPos.y * 4) + (int)(worldPos.x * 4);
	if (index < 0) index = 0;
	if (index > _mapDimensions.x * _mapDimensions.y) index = _mapDimensions.x * _mapDimensions.y;

	TileData newTile;
	newTile.xIndex = x;
	newTile.yIndex = y;
	newTile.layer = layer;
	newTile.uvCoords = new glm::vec2[4];
	newTile.uvCoords[0] = glm::vec2((x * _tileSize.x) / _spritemapResolution.x, (y * _tileSize.y) / _spritemapResolution.y);
	newTile.uvCoords[1] = glm::vec2(((x + 1) * _tileSize.x) / _spritemapResolution.x, (y * _tileSize.y) / _spritemapResolution.y);
	newTile.uvCoords[2] = glm::vec2(((x + 1) * _tileSize.x) / _spritemapResolution.x, ((y + 1) * _tileSize.y) / _spritemapResolution.y);
	newTile.uvCoords[3] = glm::vec2((x * _tileSize.x) / _spritemapResolution.x, ((y + 1) * _tileSize.y) / _spritemapResolution.y);
	_tiles[index] = newTile;
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

glm::vec2 TileMap::MousePosToTile(Camera* cam)
{
	//Get the mouse position in editor Range: (0 - 960, 0 - 540)
	glm::vec2 mousePos = Input::GetEditorMousePos();
	//std::cout << "Mouse Position: " << mousePos.x << ", " << mousePos.y << std::endl;

	//size of the editor window
	glm::vec2 windowSize = Window::GetHalfWindowSize();

	//Get the camera's position and offset it by the camera's size
	glm::vec2 camPos = cam->PositionXY();
	camPos -= cam->Size();

	glm::vec2 attempt2 = (camPos / 2.0f) + (mousePos / windowSize);
	attempt2.x = attempt2.x * (_tilesPerUnit / 2.0f);
	if (mousePos.x < windowSize.x / 8.0f) {
		attempt2.x += _tileScale * 0.5f;
	}
	else if (mousePos.x < windowSize.x / 4.0f) {
		attempt2.x += _tileScale * 1.5f;
	}
	else if (mousePos.x < windowSize.x / 8.0f + ((windowSize.x / 8.0f) * 2)) {
		attempt2.x += _tileScale * 2.5f;
	}
	else if (mousePos.x < windowSize.x / 2.0f) {
		attempt2.x += _tileScale * 3.0f;
	}
	else if (mousePos.x < windowSize.x / 2.0f + (windowSize.x / 8.0f)) {
		attempt2.x += _tileScale * 3.5f;
	}
	else if (mousePos.x < windowSize.x / 2.0f + (windowSize.x / 4.0f)) {
		attempt2.x += _tileScale * 4.5f;
	}
	else if (mousePos.x < windowSize.x / 2.0f + ((windowSize.x / 8.0f) * 3)) {
		attempt2.x += _tileScale * 5.5f;
	}
	else
	{
		attempt2.x += _tileScale * 6.0f;
	}
	attempt2.y = attempt2.y * (_tilesPerUnit / 2.0f);

	if (attempt2.x > _mapSizeInScreenUnits.x) {
		//Puts tile on upmost index
		attempt2.x = _mapSizeInScreenUnits.x - _tileScale;
	}
	if (attempt2.y > _mapSizeInScreenUnits.y) {
		//Puts tile on furthest right index
		attempt2.y = _mapSizeInScreenUnits.y - _tileScale;
	}

	return attempt2;
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

	for (float y = 0; y < _mapSizeInScreenUnits.y; y += _yGapBetweenTiles) {
		for (float x = 0; x < _mapSizeInScreenUnits.x; x += _xGapBetweenTiles) {
			if (x < camPos.x - extents || x > camPos.x + extents || y < camPos.y - extents || y > camPos.y + extents) {
				continue;
			}
			//int index = (y * (float)_tilesPerUnit) * _mapDimensions.y + (x * (float)_tilesPerUnit);
			int index = _mapDimensions.x * (int)(y * 4) + (int)(x * 4);

			if (index == _currentTileIndex) {
				Renderer2D::DrawQuad({ x,y }, { _tileScale, _tileScale }, ResourceManager::GetTexture("spritesheet"), _noTcCoords, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				continue;
			}


			if (_tiles[index].uvCoords == nullptr) {
				Renderer2D::DrawQuad({ x,y }, { _tileScale, _tileScale }, ResourceManager::GetTexture("spritesheet"), _noTcCoords);
				continue;
			}

			Renderer2D::DrawQuad({ x,y }, { _tileScale,_tileScale }, ResourceManager::GetTexture("spritesheet"), _tiles[index].uvCoords);
		}
	}

	Renderer2D::EndRender();
}