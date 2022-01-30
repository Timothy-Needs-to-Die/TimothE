#include "TileMap.h"
#include "Renderer2D.h"

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

	//int index = (int)(worldPos.y * (float)_tilesPerUnit) * _mapDimensions.y + (worldPos.x * (float)_tilesPerUnit);
	int index = _mapDimensions.x * (int)(worldPos.y * 4) + (int)(worldPos.x * 4);
	if(index < 0) index = 0;
	std::cout << "Index: " << index << std::endl;
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
	//Get the mouse position in editor
	glm::vec2 mousePos = Input::GetEditorMousePos();
	//std::cout << "Mouse Position: " << mousePos.x << ", " << mousePos.y << std::endl;

	glm::vec2 windowSize = { 960.0f, 540.0f };

	//Get the camera's position and offset it by the camera aspect ratio (X) and zoom level (y)
	glm::vec2 camPos = { cam->Position().x, cam->Position().y };
	camPos -= glm::vec2(cam->GetAspectRatio(), cam->GetZoomLevel());

	//Convert camera to pixel space
	glm::vec2 cameraInPixels = camPos * windowSize;
	//std::cout << "Camera in pixels: " << cameraInPixels.x << ", " << cameraInPixels.y << std::endl;

	//Transform camera position with the mouse position
	glm::vec2 cameraConvertedToMouse = cameraInPixels + mousePos;
	//std::cout << "Camera converted to mouse: " << cameraConvertedToMouse.x << ", " << cameraConvertedToMouse.y << std::endl;

	//Convert these coordinates into world space coordinates
	glm::vec2 convertedCoords = cameraConvertedToMouse / windowSize;
	//std::cout << "Converted coords in world space: " << convertedCoords.x << ", " << convertedCoords.y << std::endl;
	//Convert into tile space
	convertedCoords *= _tilesPerUnit / 2.0f;
	//Offset the size of each tile
	//convertedCoords -= _tileScale / 2.0f;

	float lowerBoundX = floor(convertedCoords.x);
	float lowerBoundY = floor(convertedCoords.y);

	float remainingX = convertedCoords.x - lowerBoundX;
	float remainingY = convertedCoords.y - lowerBoundY;

	if (remainingX == 0.0f) {
		convertedCoords.x = lowerBoundX;
	}
	else if (remainingX < 0.25f) {
		convertedCoords.x = lowerBoundX + 0.25f;
	}
	else if (remainingX < 0.5f) {
		convertedCoords.x = lowerBoundX + 0.5f;
	}
	else if (remainingX < 0.75f) {
		convertedCoords.x = lowerBoundX + 0.75f;
	}
	else {
		convertedCoords.x = lowerBoundX + 1.0f;
	}

	if (remainingY == 0.0f) {
		convertedCoords.y = lowerBoundY;
	}
	else if (remainingY < 0.25f) {
		convertedCoords.y = lowerBoundY + 0.25f;
	}
	else if (remainingY < 0.5f) {
		convertedCoords.y = lowerBoundY + 0.5f;
	}
	else if (remainingY < 0.75f) {
		convertedCoords.y = lowerBoundY + 0.75f;
	}
	else {
		convertedCoords.y = lowerBoundY + 1.0f;
	}

	if (convertedCoords.x > _mapSizeInScreenUnits.x) convertedCoords.x = _mapSizeInScreenUnits.x;


	//std::cout << "Converted coords: " << convertedCoords.x << ", " << convertedCoords.y << std::endl;

	

	//return convertedCoords;

	glm::vec2 processedCam = camPos * windowSize;

	glm::vec2 attempt2 = camPos + (mousePos / windowSize);
	//attempt2 += camPos;
	attempt2.x = attempt2.x;
	attempt2.y = attempt2.y * (_tilesPerUnit / 2);

	if (attempt2.x > _mapSizeInScreenUnits.x) {
		std::cout << "Greater than the map X size" << std::endl;
		attempt2.x = _mapSizeInScreenUnits.x  - _tileScale;
	}
	if (attempt2.y > _mapSizeInScreenUnits.y) {
		std::cout << "Greater than the map Y size" << std::endl;
		attempt2.y = _mapSizeInScreenUnits.y - _tileScale;
		//attempt2.x -= _tileScale;
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

	for (float y = 0; y < _mapSizeInScreenUnits.y; y+= _yGapBetweenTiles) {
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