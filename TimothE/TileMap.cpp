#include "pch.h"
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

TileMap::TileMap(std::string name)
	: _name(name)
{
	_tileArr.resize(_numLayers);

	_gapBetweenTiles = 1.0f / _tilesPerUnit;

	LoadTileMap();
}

TileMap::~TileMap()
{
}

void TileMap::ClearAllLayers()
{
	for (int i = 0; i < _numLayers; i++) {
		for (int j = 0; j < _mapInTiles.x * _mapInTiles.y; j++) {
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
		int i = 0;
		for each (TileData var in _tileArr[layer])
		{
			int index = var.texIndex;

			std::string resourceName = "spritesheet";
			if (var._pSpritesheet != nullptr) {
				resourceName = var._pSpritesheet->GetResourceName();
			}

			tileLayout += std::to_string(index) + " " + std::to_string((int)_collidableTileArray[i]) + " " + resourceName + ",";

			i++;
		}
		file["tiles" + std::to_string(layer)] = tileLayout;
	}

	outfile << file;
}

void TileMap::LoadTileMap()
{
	using nlohmann::json;

	//Construct filepath and open file
	std::string filename = "Resources/Scenes/" + _name + ".json";
	std::ifstream inFile(filename);
	//if the file is not found then output error.
	if (!inFile.good()) {
		TIM_LOG_ERROR("[ERROR: TileMap::LoadTileMap]: TileMap file: " << filename << " could not be loaded");
		return;
	}

	//Construct json object and read data from file into it
	json file;
	file << inFile;
	
	//Set map size
	SetTileMapSize({ (float)file["sizeX"], (float)file["sizeY"] });
	
	//Calculate the dimensions of the map
	int dimensions = _mapInTiles.x * _mapInTiles.y;

	//Set the tiles per unit
	_tilesPerUnit = (int)file["tilePerUnit"];

	//Create collidable array and set everything to false by default
	_collidableTileArray = new bool[dimensions];
	memset(_collidableTileArray, false, dimensions);

	//Create the lightmap array and set everything to 5 by default
	_lightLevelArray = new int[dimensions];
	for (int i = 0; i < dimensions; i++) {
		_lightLevelArray[i] = 5;
	}
	
	//Cycle through all layers
	for (int layer = 0; layer < _numLayers; layer++) {
		//check to see if we have a tile layer collection
		if (file.contains("tiles" + std::to_string(layer))) {
			//Get the entire layers information
			std::string tileInfo = file["tiles" + std::to_string(layer)];

			//Consturct tile info into a stringstream
			std::stringstream ss(tileInfo);

			//Create a vector which stores each element separated by commas
			std::vector<std::string> results;
			while (ss.good()) {
				std::string substr;
				getline(ss, substr, ',');
				results.push_back(substr);
			}

			//Cycle through the dimensions of the map
			for (int i = 0; i < dimensions; i++) {
				//create a stringstream based off the tile info
				std::stringstream ss(results[i]);

				//Read the texture index from the tile info and assign it
				std::string texIndexString;
				getline(ss, texIndexString, ' ');
				int index = std::stoi(texIndexString);
				_tileArr[layer][i].texIndex = index;

				//Read the collidable value from the tile info and assign it if needed
				std::string collidableString;
				getline(ss, collidableString, ' ');
				bool collidable = std::stoi(collidableString);
				//Ensures that a non collidable tile on layer 4 would not override a collidable tile on layer 2
				if (collidable) {
					_collidableTileArray[i] = true;
				}

				//Reads in the sprite sheet name and sets the sprites accordingly
				std::string spritesheetName;
				getline(ss, spritesheetName, ' ');
				if (spritesheetName != "") {
					_tileArr[layer][i]._pSpritesheet = ResourceManager::GetSpriteSheet(spritesheetName);
				}
				else {
					_tileArr[layer][i]._pSpritesheet = ResourceManager::GetSpriteSheet("spritesheet");
				}
				_tileArr[layer][i]._pSprite = _tileArr[layer][i]._pSpritesheet->GetSpriteAtIndex(index);


				int yIndex = i / _mapInTiles.x;
				int xIndex = i - (yIndex * _mapInTiles.x);

				float xPos = (float)xIndex * _gapBetweenTiles;
				float yPos = ((float)yIndex * _gapBetweenTiles);
				glm::vec2 colPos = glm::vec2(xPos, yPos);
				_tileArr[layer][i].pos = { xPos, yPos };

				_tileArr[layer][i].size = _gapBetweenTiles;
			}
		}
		else {
			for (int i = 0; i < dimensions; i++) {
				_tileArr[layer][i].texIndex = 0;
				_tileArr[layer][i]._pSprite = ResourceManager::GetSpriteSheet("spritesheet")->GetSpriteAtIndex(0);
				_collidableTileArray[i] = false;

				int yIndex = i / _mapInTiles.x;
				int xIndex = i - (yIndex * _mapInTiles.x);

				float xPos = (float)xIndex * _gapBetweenTiles;
				float yPos = ((float)yIndex * _gapBetweenTiles);

				glm::vec2 colPos = glm::vec2(xPos, yPos);
				_tileArr[layer][i].pos = { xPos, yPos };
				_tileArr[layer][i].size = _gapBetweenTiles;
			}
		}
	}


	for (int layer = 0; layer < _numLayers; layer++) {
		RendererData data = Renderer2D::GenerateRendererData();

		for (int i = 0; i < dimensions; i++) {
			TileData& td = _tileArr[layer][i];
			glm::vec2 pos = td.pos;

			if (td._pSprite == nullptr) continue;

			Renderer2D::AddData(data, Quad{ { pos.x, pos.y}, {0.25f, 0.25f} }, td._pSprite->GetTexture(), td._pSprite->GetTexCoords());
		}

		_tilemapRendererData.emplace_back(data);
	}

}

void TileMap::AddTileAt(unsigned int layer, unsigned int uvX, unsigned int uvY, Camera* cam, SpriteSheet* sp, bool shouldCollide /*= false*/)
{
	if (sp == nullptr) return;

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

	if (shouldCollide) {
		_collidableTileArray[index] = true;
	}

	newTile.size = _gapBetweenTiles;
	newTile.pos = colPos;

	newTile._pSpritesheet = sp;
	newTile._pSprite = sp->GetSpriteAtIndex(sp->GetSheetWidth() * uvY + uvX);
	_tileArr[layer][index] = newTile;
}

void TileMap::FillLayer(unsigned int layer, int uvX, int uvY, SpriteSheet* sp)
{
	if (sp == nullptr) return;

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


	return convertedPosition;
}

//Sets the size of the tilemap in tiles. e.g a 256 x 140 tile map.
void TileMap::SetTileMapSize(glm::vec2 mapSize)
{
	_mapInTiles = mapSize;
	int elementSize = _mapInTiles.x * _mapInTiles.y;

	for (int i = 0; i < _tileArr.size(); i++) {
		_tileArr[i].resize(elementSize);
	}

	_mapSizeInUnits = glm::vec2(_mapInTiles.x / _tilesPerUnit, _mapInTiles.y / _tilesPerUnit);
}

TileData* TileMap::GetTileAtWorldPos(int layer, glm::vec2 worldPos)
{
	if (worldPos.y < 0.0f) worldPos.y = 0.0f;
	else if (worldPos.y > _mapSizeInUnits.y) worldPos.y = _mapSizeInUnits.y;

	if (worldPos.x < 0.0f) worldPos.x = 0.0f;
	else if (worldPos.x > _mapSizeInUnits.x) worldPos.x = _mapSizeInUnits.x;

	//Calculates the index of the tile
	int index = _mapInTiles.x * (int)(worldPos.y * _tilesPerUnit) + (int)(worldPos.x * _tilesPerUnit);

	//Protection incase specified position results in a tile outside of the map
	if (index < 0) index = 0;
	if (index > _mapInTiles.x * _mapInTiles.y) index = (_mapInTiles.x * _mapInTiles.y) - 1;

	//Gets the tile on the specified layer
	return &_tileArr[layer][index];
}

void TileMap::ClearLayer(int layer)
{
	if (layer < 0) layer = 0;
	if (layer >= _numLayers) layer = _numLayers - 1;

	//Cycle through all tiles on this layer and remove their sprite
	for (int i = 0; i < _mapInTiles.x * _mapInTiles.y; i++) {
		_tileArr[layer][i] = TileData();
	}
}

void TileMap::RenderMap(Camera* cam)
{
	for (int i = 0; i < _tilemapRendererData.size(); i++) {
		RendererData& data = _tilemapRendererData[i];
		data.textureShader->SetMat4("view", cam->ViewProj());

		if (data.quadIndexCount != 0) {
			uint32_t dataSize = (uint32_t)((uint8_t*)data.quadVertexBufferPtr - (uint8_t*)data.quadVertexBufferBase);
			data.quadVertexBuffer->SetData(data.quadVertexBufferBase, dataSize);

			for (unsigned int i = 0; i < data.textureSlotIndex; i++) {
				data.textureSlots[i]->Bind(i);
			}

			data.textureShader->BindShader();

			Renderer2D::DrawIndexed(data.quadVertexArray, data.quadIndexCount);
		}
	}
}

bool TileMap::CollidableAtPosition(const int x, const int y) const
{
	int tIndex = y * _mapInTiles.x + x;

	return _collidableTileArray[tIndex];
}

bool TileMap::CollidableAtPosition(glm::vec2 worldPos)
{
	TileData* td = GetTileAtWorldPos(0, worldPos);

	int index = _mapInTiles.x * (int)(worldPos.y * _tilesPerUnit) + (int)(worldPos.x * _tilesPerUnit);

	return CollidableAtPosition(index);
}

void TileMap::UpdateLightLevelAtPosition(glm::vec2 pos, int lightLevel)
{
	//Convert position to a single dimension index.
	int index = GetTileIndexFromPosition(pos);

	_lightLevelArray[index] = lightLevel;

	//Multiply index by 4 so it is quad vertex space
	index *= 4;

	//Loops through each layer of render data
	for (int i = 0; i < _tilemapRendererData.size(); ++i) {
		//Sets the light level on the four different vertices of the quad.
		_tilemapRendererData[i].quadVertexBufferBase[index].lightLevel = lightLevel;
		_tilemapRendererData[i].quadVertexBufferBase[index + 1].lightLevel = lightLevel;
		_tilemapRendererData[i].quadVertexBufferBase[index + 2].lightLevel = lightLevel;
		_tilemapRendererData[i].quadVertexBufferBase[index + 3].lightLevel = lightLevel;
	}
}

void TileMap::UpdateRenderInfo()
{
	for (int i = 0; i < _tilemapRendererData.size(); ++i) {
		uint32_t dataSize = (uint32_t)((uint8_t*)_tilemapRendererData[i].quadVertexBufferPtr - (uint8_t*)_tilemapRendererData[i].quadVertexBufferBase);
		_tilemapRendererData[i].quadVertexBuffer->SetData(_tilemapRendererData[i].quadVertexBufferBase, dataSize);
	}
}

void TileMap::SetCollidableAtPosition(glm::vec2 pos, bool val)
{
	int index = GetTileIndexFromPosition(pos);

	_collidableTileArray[index] = val;
}

int TileMap::GetTileIndexFromPosition(glm::vec2 pos)
{
	int index = _mapInTiles.x * (int)(pos.y * _tilesPerUnit) + (int)(pos.x * _tilesPerUnit);
	return index;
}

bool TileMap::CollidableAtPosition(const int index) const
{
	if (index < 0 || index > _tileArr[0].size()) return false;

	return _collidableTileArray[index];
}

void TileMap::SetAllTilesLightLevel(int level)
{
	for (int i = 0; i < _mapInTiles.x * _mapInTiles.y; ++i) {
		UpdateLightLevelAtPosition(_tileArr[0][i].pos, level);
	}

	UpdateRenderInfo();
}

int TileMap::GetLightLevelAtPosition(glm::vec2 pos)
{
	int index = GetTileIndexFromPosition(pos);
	return _lightLevelArray[index];
}

