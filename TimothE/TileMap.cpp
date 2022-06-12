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

//TODO: Single collision map
//TODO: Single light value map

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

	SetTileMapSize(_mapInTiles);

	_tilesPerUnit = (int)file["tilePerUnit"];

	int dimensions = _mapInTiles.x * _mapInTiles.y;

	_collidableTileArray = new bool[dimensions];

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
				//_tileArr[layer][i].collidable = collidable;

				if (collidable) {
					_collidableTileArray[i] = true;
				}

				int row = i / _mapInTiles.x;
				int xIndex = i - (row * _mapInTiles.x);

				float xPos = (float)xIndex * _gapBetweenTiles;
				float yPos = ((float)row * _gapBetweenTiles);
				glm::vec2 colPos = glm::vec2(xPos, yPos);
				_tileArr[layer][i].pos = { xPos, yPos };

				_tileArr[layer][i].size = _gapBetweenTiles;
			}
		}
		else {
			for (int i = 0; i < dimensions; i++) {

				int index = 0;

				bool collidable = false;

				_tileArr[layer][i].texIndex = index;
				_tileArr[layer][i]._pSprite = ResourceManager::GetSpriteSheet("spritesheet")->GetSpriteAtIndex(0);
				_collidableTileArray[i] = collidable;

				int row = i / _mapInTiles.x;
				int xIndex = i - (row * _mapInTiles.x);

				float xPos = (float)xIndex * _gapBetweenTiles;
				float yPos = ((float)row * _gapBetweenTiles);
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
	newTile.lightLevel = 5;

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
	int yIndex = pos.y / _gapBetweenTiles;
	int xIndex = pos.x / _gapBetweenTiles;
	int index = (yIndex * _mapInTiles.x) + xIndex;

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
	TileData* td = GetTileAtWorldPos(0, pos);

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
	//loop through all tiles in map and set light level
	for (int y = 0; y < 5; y++)
	{
		for (int i = 0; i < _tileArr[y].size(); ++i) {
			_tileArr[y][i].lightLevel = level;
		}
	}
}
