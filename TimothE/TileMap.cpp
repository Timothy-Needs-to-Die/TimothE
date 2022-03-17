#include "TileMap.h"
#include "Renderer2D.h"
#include "Window.h"


std::ostream& operator<<(std::ostream& os, glm::vec2 v) {
	os << "X: " << v.x << " Y: " << v.y;
	return os;
}

//TODO: Size details
//TODO: Add a system to change how many tiles per unit
TileMap::TileMap()
{
	_mapDimensions = { 20.0f, 20.0f };
	_mapSizeInScreenUnits = glm::vec2(_mapDimensions.x / _tilesPerUnit, _mapDimensions.y / _tilesPerUnit);
	_tileSize = glm::vec2(128.0f);
	_spritemapResolution = glm::vec2(2560.0f, 1664.0f);

	int elementSize = _mapDimensions.x * _mapDimensions.y;
	_tileArr[0].resize(elementSize);
	_tileArr[1].resize(elementSize);
	_tileArr[2].resize(elementSize);

	_xGapBetweenTiles = 1.0f / _tilesPerUnit;
	_yGapBetweenTiles = 1.0f / _tilesPerUnit;

	_tileScale = 1.0f / _tilesPerUnit;

	_noTcCoords = new glm::vec2[4];
	_noTcCoords[0] = glm::vec2((1 * _tileSize.x) / _spritemapResolution.x, (11 * _tileSize.y) / _spritemapResolution.y);
	_noTcCoords[1] = glm::vec2(((1 + 1) * _tileSize.x) / _spritemapResolution.x, (11 * _tileSize.y) / _spritemapResolution.y);
	_noTcCoords[2] = glm::vec2(((1 + 1) * _tileSize.x) / _spritemapResolution.x, ((11 + 1) * _tileSize.y) / _spritemapResolution.y);
	_noTcCoords[3] = glm::vec2((1 * _tileSize.x) / _spritemapResolution.x, ((11 + 1) * _tileSize.y) / _spritemapResolution.y);

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

void TileMap::AddTileAt(unsigned int layer, unsigned int x, unsigned int y, Camera* cam, bool shouldCollide)
{
	glm::vec2 worldPos = MousePosToTile(cam);

	int index = _mapDimensions.x * (int)(worldPos.y * _tilesPerUnit) + (int)(worldPos.x * _tilesPerUnit);
	if (index < 0) index = 0;
	if (index > _mapDimensions.x * _mapDimensions.y) index = _mapDimensions.x * _mapDimensions.y;

	int xTiles = worldPos.x * _tilesPerUnit;
	int yTiles = worldPos.y * _tilesPerUnit;

	float xPos = (float)xTiles * _tileScale;
	float yPos = (float)yTiles * _tileScale;
	glm::vec2 colPos = glm::vec2(xPos, yPos);

	TileData newTile;
	newTile.xIndex = x;
	newTile.yIndex = y;
	newTile.layer = layer;
	newTile.collidable = shouldCollide;
	newTile.size = _xGapBetweenTiles;
	newTile.colXPos = colPos.x;
	newTile.colYPos = colPos.y;


	newTile._pSpritesheet = _pSpritesheet;
	newTile._pSprite = _pSpritesheet->GetSpriteAtIndex(_pSpritesheet->GetSheetWidth() * y + x);
	_tileArr[layer][index] = newTile;
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

void TileMap::FillLayer(unsigned int layer, int uvX, int uvY)
{
	for (int i = 0; i < _tileArr[layer].size(); i++) {
		_tileArr[layer][i]._pSpritesheet = _pSpritesheet;
		_tileArr[layer][i]._pSprite = _pSpritesheet->GetSpriteAtIndex(_pSpritesheet->GetSheetWidth() * uvY + uvX);
	}
}

glm::vec2 TileMap::GetTileSize() const
{
	return glm::vec2();
}

glm::vec2 TileMap::MousePosToTile(Camera* cam)
{
	glm::vec2 mousePos = Input::GetEditorMousePos();
	glm::vec2 camPos = cam->PositionXY();
	glm::vec2 convertedPosition = camPos + mousePos;

	if (convertedPosition.x > _mapSizeInScreenUnits.x) {
		//Puts tile on upmost index
		convertedPosition.x = _mapSizeInScreenUnits.x - _tileScale;
	}
	if (convertedPosition.y > _mapSizeInScreenUnits.y) {
		//Puts tile on furthest right index
		convertedPosition.y = _mapSizeInScreenUnits.y - _tileScale;
	}
	
	//std::cout << "Camera Pos: " << camPos << std::endl;
	//std::cout << "Mouse Pos: " << mousePos << std::endl;
	//std::cout << "Converted Pos: " << convertedPosition << std::endl << std::endl;

	return convertedPosition;
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

TileData* TileMap::GetTileAtWorldPos(int layer, glm::vec2 worldPos)
{
	int index = _mapDimensions.x * (int)(worldPos.y * _tilesPerUnit) + (int)(worldPos.x * _tilesPerUnit);
	if (index < 0) index = 0;
	if (index > _mapDimensions.x * _mapDimensions.y) index = _mapDimensions.x * _mapDimensions.y;

	return &_tileArr[layer][index];
}

void TileMap::Clear()
{
}

void TileMap::RenderMap(Camera* cam)
{
	glm::vec3 camPos = cam->Position();
	float extents = cam->GetAspectRatio() * cam->GetZoomLevel() * 2.0f;
	Renderer2D::BeginRender(cam);

	for (int i = 0; i < 3; i++) {
		for (float y = 0; y < _mapSizeInScreenUnits.y; y += _yGapBetweenTiles) {
			for (float x = 0; x < _mapSizeInScreenUnits.x; x += _xGapBetweenTiles) {
				if (x < camPos.x - extents || x > camPos.x + extents || y < camPos.y - extents || y > camPos.y + extents) {
					continue;
				}
				int index = _mapDimensions.x * (int)(y * 4) + (int)(x * 4);

				//if (index == _currentTileIndex) {
				//	//Renderer2D::DrawQuad({ x,y }, { _tileScale, _tileScale }, ResourceManager::GetTexture("spritesheet"), _noTcCoords, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				//	continue;
				//}


				if (_tileArr[i][index]._pSprite == nullptr) {
					//Renderer2D::DrawQuad({ x,y }, { _tileScale, _tileScale }, ResourceManager::GetTexture("spritesheet"), _noTcCoords);
					continue;
				}

				Renderer2D::DrawQuad({ x,y }, { _tileScale,_tileScale }, _tileArr[i][index]._pSprite->GetTexture(), _tileArr[i][index]._pSprite->GetTexCoords());
			}
		}
	}

	Renderer2D::EndRender();
}