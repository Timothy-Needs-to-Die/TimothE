#include "TileMap.h"
#include "Core/Graphics/Renderer2D.h"
#include "Core/Graphics/Window.h"
#include "Quad.h"
#include "TileMapEditor.h"


std::ostream& operator<<(std::ostream& os, glm::vec2 v) {
	os << "X: " << v.x << " Y: " << v.y;
	return os;
}

//TODO: Size details
//TODO: Add a system to change how many tiles per unit
TileMap::TileMap(std::string name)
	: _name(name)
{
	_tileArr = new std::vector<TileData>[_numLayers];
	SetTileMapSize({ 32.0f, 32.0f });

	_tileSize = glm::vec2(128.0f);

	_gapBetweenTiles = 1.0f / _tilesPerUnit;

	SetSpriteSheet(ResourceManager::GetSpriteSheet("testSheet"));
	LoadTileMap();

}

TileMap::~TileMap()
{
}

void TileMap::ClearAllLayers()
{
	for (int i = 0; i < _numLayers; i++) {
		for (int j = 0; j < _mapInTiles.x * _mapInTiles.y; j++) {
			//_tileArr[i][j]._pSprite = nullptr;
			//_tileArr[i][j].texIndex = 0;
			_tileArr[i][j] = TileData();
		}
	}
}

void TileMap::UpdateLogic(Camera* cam)
{
	_currentTile = MousePosToTile(cam);
	_currentTileIndex = _mapInTiles.x * (int)(_currentTile.y * 4) + (int)(_currentTile.x * 4);
}

void TileMap::SaveTilemap() {
	using nlohmann::json;

	//TODO: Change to use the current scene instead

	std::string filename = "Resources/Scenes/" + _name + ".json";
	std::ofstream outfile(filename);

	json file;

	//TODO: Change this to getting the spritesheet name
	file["spritesheet"] = "testSheet";

	file["sizeX"] = _mapInTiles.x;
	file["sizeY"] = _mapInTiles.y;
	file["tilePerUnit"] = _tilesPerUnit;

	for (int layer = 0; layer < _numLayers; layer++) {
		std::string tileLayout;
		for each (TileData var in _tileArr[layer])
		{
			int index = var.texIndex;

			tileLayout += std::to_string(index) + " " + std::to_string((int)var.collidable) + ",";
		}
		file["tiles" + std::to_string(layer)] = tileLayout;
	}


	outfile << file;
}

void TileMap::LoadTileMap()
{
	using nlohmann::json;
	std::string filename = "Resources/Scenes/" + _name + ".json";
	std::ifstream inFile(filename);

	if (!inFile.good()) {
		std::cout << "[ERROR: TileMap::LoadTileMap]: TileMap file: " << filename << " could not be loaded" << std::endl;
		return;
	}

	json file;

	file << inFile;

	_mapInTiles.x = (float)file["sizeX"];
	_mapInTiles.y = (float)file["sizeY"];

	_tilesPerUnit = (int)file["tilePerUnit"];

	int dimensions = _mapInTiles.x * _mapInTiles.y;
	
	for (int layer = 0; layer < _numLayers; layer++) {
		_tileArr[layer].resize(dimensions);
		std::string tileInfo = file["tiles" + std::to_string(layer)];
		std::stringstream ss(tileInfo);

		std::vector<std::string> results;
		while (ss.good()) {
			std::string substr;
			getline(ss, substr, ',');
			results.push_back(substr);
		}

		for (int i = 0; i < dimensions; i++) {

			//std::cout << results[i] << std::endl;

			std::stringstream ss(results[i]);
			std::string s1;
			getline(ss, s1, ' ');
			std::string s2;
			getline(ss, s2, ' ');

			int index = std::stoi(s1);

			bool collidable = std::stoi(s2);

			_tileArr[layer][i].texIndex = index;
			_tileArr[layer][i]._pSprite = _pSpritesheet->GetSpriteAtIndex(index);
			_tileArr[layer][i].collidable = collidable;

			int row = i / _mapInTiles.x;
			int xIndex = i - (row * _mapInTiles.x);

			if (collidable) {
				std::cout << "Tile at X: " << xIndex << ", Y: " << row << std::endl;
			}
			//int xIndex = 

			float xPos = (float)xIndex * _gapBetweenTiles;
			float yPos = ((float)row * _gapBetweenTiles);
			glm::vec2 colPos = glm::vec2(xPos, yPos);
			_tileArr[layer][i].colXPos = xPos;
			_tileArr[layer][i].colYPos = yPos;

			_tileArr[layer][i].size = _gapBetweenTiles;
		}
	}

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
	newTile.texIndex = uvY * _pSpritesheet->GetSheetWidth() + uvX;
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
		_tileArr[layer][i].texIndex = uvY * _pSpritesheet->GetSheetWidth() + uvX;
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
		_tileArr[layer][i] = TileData();
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
	for (int i = 0; i < _numLayers; i++) {
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

				if (TileMapEditor::_showCollisionMap) {
					glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
					if (!_tileArr[i][index].collidable) {
						color.r = 0.0f;
						color.g = 1.0f;
					}
					Renderer2D::DrawQuad(Quad{ { x,y }, { _gapBetweenTiles,_gapBetweenTiles } }, _tileArr[i][index]._pSprite->GetTexture(), _tileArr[i][index]._pSprite->GetTexCoords(), color);
				}
				else {
					//Draw this tile
					Renderer2D::DrawQuad(Quad{ { x,y }, { _gapBetweenTiles,_gapBetweenTiles } }, _tileArr[i][index]._pSprite->GetTexture(), _tileArr[i][index]._pSprite->GetTexCoords());
				}
			}
		}
	}

	//Ends the batch render for the tilemap
	Renderer2D::EndRender();
}

bool TileMap::CollidableAtPosition(const int x, const int y) const
{
	int tIndex = y * _mapInTiles.x + x;
	for (int layer = 0; layer < _numLayers; layer++) {
		if (_tileArr[layer][tIndex].collidable) return true;
	}
	return false;
}

bool TileMap::CollidableAtPosition(glm::vec2 worldPos)
{
	TileData* td = GetTileAtWorldPos(0, worldPos);
	
	int index = _mapInTiles.x * (int)(worldPos.y * _tilesPerUnit) + (int)(worldPos.x * _tilesPerUnit);
	
	return CollidableAtPosition(index);
}

bool TileMap::CollidableAtPosition(const int index)
{
	for (int layer = 0; layer < _numLayers; layer++) {
		if (_tileArr[layer][index].collidable) return true;
	}
	return false;
}
