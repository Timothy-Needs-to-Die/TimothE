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
	SetTileMapSize({ 32.0f, 32.0f });

	_tileSize = glm::vec2(128.0f);

	_gapBetweenTiles = 1.0f / _tilesPerUnit;
}

TileMap::~TileMap()
{
}

void TileMap::CreateTileMap() {
	//using nlohmann::json;
	//std::ifstream file(_tileMapFile);
	//if (!file) {
	//	std::cout << "Unable to open file" << _tileMapFile << std::endl;
	//	return;
	//}
	//json root;
	//file >> root;
	//
	//_tileSize.x = root["TILE_WIDTH"];
	//_tileSize.y = root["TILE_HEIGHT"];
	//
	//_mapSizeInScreenUnits.x = root["WIDTH"];
	//_mapSizeInScreenUnits.y = root["HEIGHT"];
	//
	//const auto& layers = root["LAYERS"];
	//_spritesheetName = root["TEXTURE_NAME"];
	//auto texturePtr = ResourceManager::GetTexture(_spritesheetName);
	//
	//if (!texturePtr)
	//{
	//	std::cout << "Error: Tilemap Texture not found" << std::endl;
	//	return;
	//}
}

void TileMap::ClearAllLayers()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < _mapInTiles.x * _mapInTiles.y; j++) {
			_tileArr[i][j]._pSprite = nullptr;
		}
	}
}

void TileMap::UpdateLogic(Camera* cam)
{
	_currentTile = MousePosToTile(cam);
	_currentTileIndex = _mapInTiles.x * (int)(_currentTile.y * 4) + (int)(_currentTile.x * 4);
}

void TileMap::AddTileAt(unsigned int layer, unsigned int uvX, unsigned int uvY, Camera* cam, bool shouldCollide /*= false*/)
{
	if (_pSpritesheet == nullptr) return;

	glm::vec2 worldPos = MousePosToTile(cam);

	int index = _mapInTiles.x * (int)(worldPos.y * _tilesPerUnit) + (int)(worldPos.x * _tilesPerUnit);
	if (index < 0) index = 0;
	if (index > _mapInTiles.x * _mapInTiles.y) index = _mapInTiles.x * _mapInTiles.y;

	int xTiles = worldPos.x * _tilesPerUnit;
	int yTiles = worldPos.y * _tilesPerUnit;

	float xPos = (float)xTiles * _gapBetweenTiles;
	float yPos = (float)yTiles * _gapBetweenTiles;
	glm::vec2 colPos = glm::vec2(xPos, yPos);

	TileData newTile;
	newTile.xIndex = uvX;
	newTile.yIndex = uvY;
	newTile.layer = layer;
	newTile.collidable = shouldCollide;
	newTile.size = _gapBetweenTiles;
	newTile.colXPos = colPos.x;
	newTile.colYPos = colPos.y;


	newTile._pSpritesheet = _pSpritesheet;
	newTile._pSprite = _pSpritesheet->GetSpriteAtIndex(_pSpritesheet->GetSheetWidth() * uvY + uvX);
	_tileArr[layer][index] = newTile;
}

void TileMap::FillLayer(unsigned int layer, int uvX, int uvY)
{
	for (int i = 0; i < _tileArr[layer].size(); i++) {
		_tileArr[layer][i]._pSpritesheet = _pSpritesheet;
		_tileArr[layer][i]._pSprite = _pSpritesheet->GetSpriteAtIndex(_pSpritesheet->GetSheetWidth() * uvY + uvX);
	}
}

glm::vec2 TileMap::MousePosToTile(Camera* cam)
{
	glm::vec2 mousePos = Input::GetEditorMousePos();
	glm::vec2 camPos = cam->PositionXY();
	glm::vec2 convertedPosition = camPos + mousePos;

	if (convertedPosition.x > _mapSizeInUnits.x) {
		//Puts tile on upmost index
		convertedPosition.x = _mapSizeInUnits.x - _gapBetweenTiles;
	}
	if (convertedPosition.y > _mapSizeInUnits.y) {
		//Puts tile on furthest right index
		convertedPosition.y = _mapSizeInUnits.y - _gapBetweenTiles;
	}
	
	//std::cout << "Camera Pos: " << camPos << std::endl;
	//std::cout << "Mouse Pos: " << mousePos << std::endl;
	//std::cout << "Converted Pos: " << convertedPosition << std::endl << std::endl;

	return convertedPosition;
}

TileData* TileMap::GetTileAtWorldPos(int layer, glm::vec2 worldPos)
{
	//Calculates the index of the tile
	int index = _mapInTiles.x * (int)(worldPos.y * _tilesPerUnit) + (int)(worldPos.x * _tilesPerUnit);

	//Protection incase specified position results in a tile outside of the map
	if (index < 0) index = 0;
	if (index > _mapInTiles.x * _mapInTiles.y) index = _mapInTiles.x * _mapInTiles.y;

	//Gets the tile on the specified layer
	return &_tileArr[layer][index];
}

void TileMap::ClearLayer(int layer)
{
	//Cycle through all tiles on this layer and remove their sprite
	for (int i = 0; i < _mapInTiles.x * _mapInTiles.y; i++) {
		_tileArr[layer][i]._pSprite = nullptr;
	}
}

void TileMap::RenderMap(Camera* cam)
{
	//Gets the camera position
	glm::vec3 camPos = cam->Position();

	//Calculate the extents of the camera based on the aspect ratio and zoom level. 
	//Multiplying by 2 stops tiles suddenly being rendered or unrendered. 
	float extents = cam->GetAspectRatio() * cam->GetZoomLevel() * 2.0f;

	//Pre-calculate the min and max values of the camera's extents to avoid recalculating them. Optimisation 
	float xMin = camPos.x - extents;
	float xMax = camPos.x + extents;
	float yMin = camPos.y - extents;
	float yMax = camPos.y + extents;

	//Start the batch render for the tilemap
	Renderer2D::BeginRender(cam);

	//Cycle through each layer
	for (int i = 0; i < 3; i++) {
		//Cycle through the Y axis
		for (float y = 0; y < _mapSizeInUnits.y; y += _gapBetweenTiles) {
			//Cycle through the X axis
			for (float x = 0; x < _mapSizeInUnits.x; x += _gapBetweenTiles) {
				//If the tile is outside of the cameras range
				if (x < xMin || x > xMax || y < yMin || y > yMax) continue;

				//Get the index of the tile
				int index = _mapInTiles.x * (int)(y * _tilesPerUnit) + (int)(x * _tilesPerUnit);

				//if this tile does not have a sprite then go to next cycle
				if (_tileArr[i][index]._pSprite == nullptr) continue;

				//Draw this tile
				Renderer2D::DrawQuad({ x,y }, { _gapBetweenTiles,_gapBetweenTiles }, _tileArr[i][index]._pSprite->GetTexture(), _tileArr[i][index]._pSprite->GetTexCoords());
			}
		}
	}

	//Ends the batch render for the tilemap
	Renderer2D::EndRender();
}