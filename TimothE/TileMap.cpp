#include "TileMap.h"
#include "Core/Graphics/Renderer2D.h"
#include "Core/Graphics/Window.h"
#include "Quad.h"
#include "TileMapEditor.h"
#include "Core.h"


std::ostream& operator<<(std::ostream& os, glm::vec2 v) {
	os << "X: " << v.x << " Y: " << v.y;
	return os;
}

//TODO: Size details
//TODO: Add a system to change how many tiles per unit
TileMap::TileMap(std::string name)
	: _name(name)
{
	_tileArr.resize(_numLayers);
	//_tileArr = new std::vector<TileData>[_numLayers];
	SetTileMapSize({ 256.0f, 32.0f });

	_tileSize = glm::vec2(128.0f);

	_gapBetweenTiles = 1.0f / _tilesPerUnit;

	//SetSpriteSheet(ResourceManager::GetSpriteSheet("testSheet"));
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

			tileLayout += std::to_string(index) + " " + std::to_string((int)var.collidable) + " " + var._pSpritesheet->GetResourceName() + ",";
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
		TIM_LOG_ERROR("[ERROR: TileMap::LoadTileMap]: TileMap file: " << filename << " could not be loaded");
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

		if (file.contains("tiles" + std::to_string(layer))) {
			std::string tileInfo = file["tiles" + std::to_string(layer)];
			std::stringstream ss(tileInfo);

			std::vector<std::string> results;
			while (ss.good()) {
				std::string substr;
				getline(ss, substr, ',');
				results.push_back(substr);
			}

			for (int i = 0; i < dimensions; i++) {
				std::stringstream ss(results[i]);
				std::string s1;
				getline(ss, s1, ' ');
				std::string s2;
				getline(ss, s2, ' ');

				
				std::string s3;
				getline(ss, s3, ' ');

				if (s3 != "") {
					std::string resourceName = s3;
					_tileArr[layer][i]._pSpritesheet = ResourceManager::GetSpriteSheet(resourceName);
				}
				else {
					_tileArr[layer][i]._pSpritesheet = ResourceManager::GetSpriteSheet("spritesheet");
				}
				int index = std::stoi(s1);

				bool collidable = std::stoi(s2);


				_tileArr[layer][i].texIndex = index;
				_tileArr[layer][i]._pSprite = _tileArr[layer][i]._pSpritesheet->GetSpriteAtIndex(index);
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
		else {
			for (int i = 0; i < dimensions; i++) {

				int index = 0;

				bool collidable = false;

				_tileArr[layer][i].texIndex = index;
				_tileArr[layer][i]._pSprite = ResourceManager::GetSpriteSheet("testSheet")->GetSpriteAtIndex(0);
				_tileArr[layer][i].collidable = collidable;

				int row = i / _mapInTiles.x;
				int xIndex = i - (row * _mapInTiles.x);

				float xPos = (float)xIndex * _gapBetweenTiles;
				float yPos = ((float)row * _gapBetweenTiles);
				glm::vec2 colPos = glm::vec2(xPos, yPos);
				_tileArr[layer][i].colXPos = xPos;
				_tileArr[layer][i].colYPos = yPos;

				_tileArr[layer][i].size = _gapBetweenTiles;
			}
		}
	}

}

void TileMap::AddTileAt(unsigned int layer, unsigned int uvX, unsigned int uvY, Camera* cam, SpriteSheet* sp, bool shouldCollide /*= false*/)
{
	//if (_pSpritesheet == nullptr) return;

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
	newTile.texIndex = uvY * sp->GetSheetWidth() + uvX;
	newTile.layer = layer;
	newTile.collidable = shouldCollide;
	newTile.size = _gapBetweenTiles;
	newTile.colXPos = colPos.x;
	newTile.colYPos = colPos.y;


	newTile._pSpritesheet = sp;
	newTile._pSprite = sp->GetSpriteAtIndex(sp->GetSheetWidth() * uvY + uvX);
	_tileArr[layer][index] = newTile;
}

void TileMap::FillLayer(unsigned int layer, int uvX, int uvY, SpriteSheet* sp)
{
	for (int i = 0; i < _tileArr[layer].size(); i++) {
		_tileArr[layer][i].texIndex = uvY * sp->GetSheetWidth() + uvX;
		_tileArr[layer][i]._pSpritesheet = sp;
		_tileArr[layer][i]._pSprite = sp->GetSpriteAtIndex(sp->GetSheetWidth() * uvY + uvX);
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

	float extents = cam->GetAspectRatio() + 5.0f;
	//float extents = 7.0f;

	//Pre-calculate the min and max values of the camera's extents to avoid recalculating them. Optimisation 
	float xMin = camPos.x - extents;
	float xMax = camPos.x + extents;
	float yMin = camPos.y - extents;
	float yMax = camPos.y + extents;

	if (xMin < 0) xMin = 0.0f;
	if (xMax > _mapSizeInUnits.x) xMax = _mapSizeInUnits.x;
	if (yMin < 0) yMin = 0.0f;
	if (yMax > _mapSizeInUnits.y) yMax = _mapSizeInUnits.y;

	//Start the batch render for the tilemap
	Renderer2D::BeginRender(cam);

	//Using this if check here means that we don't have to do the if check inside each tile, massively reducing comparisons on each tile (roughly 9000 comparisons per frame)
	if (TileMapEditor::_showCollisionMap) {
		//Predefine these here to reduce the amount of created objects inside the loop.
		glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		glm::vec4 color;

		//Cycle through each layer
		for (int i = 0; i < _numLayers; i++) {
			//Cycle through the Y axis
			for (float y = yMin; y <= yMax; y += _gapBetweenTiles) {
				//Cycle through the X axis
				for (float x = xMin; x <= xMax; x += _gapBetweenTiles) {

					//Get the index of the tile
					int index = _mapInTiles.x * (int)(y * _tilesPerUnit) + (int)(x * _tilesPerUnit);

					//if this tile does not have a sprite then go to next cycle
					if (_tileArr[i][index]._pSprite == nullptr) continue;

					//Decide the color based on the tiles collidability
					color = (_tileArr[i][index].collidable) ? red : green;

					Renderer2D::DrawQuad(Quad{ { x,y }, { _gapBetweenTiles,_gapBetweenTiles } }, _tileArr[i][index]._pSprite->GetTexture(), _tileArr[i][index]._pSprite->GetTexCoords(), color);
				}
			}
		}
	}
	else {
		//Cycle through each layer
		for (int i = 0; i < _numLayers; i++) {
			//Cycle through the Y axis
			for (float y = yMin; y <= yMax; y += _gapBetweenTiles) {
				//Cycle through the X axis
				for (float x = xMin; x <= xMax; x += _gapBetweenTiles) {

					//Get the index of the tile
					int index = _mapInTiles.x * (int)(y * _tilesPerUnit) + (int)(x * _tilesPerUnit);

					//if this tile does not have a sprite then go to next cycle
					if (_tileArr[i][index]._pSprite == nullptr) continue;

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
