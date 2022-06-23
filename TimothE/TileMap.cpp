#include "pch.h"
#include "TileMap.h"
#include "Core/Graphics/Renderer2D.h"
#include "Core/Graphics/Window.h"
#include "Quad.h"
#include "TileMapEditor.h"
#include "Time.h"
#include "Core.h"

#include "TSXParser.h"
#include "TMXParser.h"


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
	TMX::Parser tmx("Resources/Tilemaps/TileMapTMXTest.tmx");

	//TODO: Figure out some form of object name position map that can be queried to find player spawn etc


	SetTileMapSize({ tmx.mapInfo.width, tmx.mapInfo.height });
	int dimensions = tmx.mapInfo.width * tmx.mapInfo.height;

	_collidableTileArray = new bool[dimensions];
	memset(_collidableTileArray, false, dimensions);

	_lightLevelArray = new int[dimensions];
	for (int i = 0; i < dimensions; ++i) {
		_lightLevelArray[i] = 5;
	}

	//Get the number of layers
	int noOfLayers = tmx.tileLayer.size();
	int currentLayer = 0;

	std::unordered_map<std::string, TSX::Parser> tileSets;
	for (int i = 0; i < tmx.tilesetList.size(); ++i) {
		std::string name = tmx.tilesetList[i].source;
		TSX::Parser tileset;
		tileset.load(("Resources/Tilemaps/" + name).c_str());
		tileSets.insert(std::make_pair(name, tileset));
	}

	//Iterate through each layer
	for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
		//Load the content into a string stream
		std::stringstream ss(tmx.tileLayer[it->first].data.contents);

		//Create a vector which stores each element separated by commas
		std::vector<std::string> results;
		while (ss.good()) {
			std::string substr;
			getline(ss, substr, ',');
			results.push_back(substr);
		}

		//Cycles through each index in the results vector
		for (int i = 0; i < results.size(); ++i) {
			int texID = std::stoi(results[i]);
			int trueID = texID;

			//Reads in the sprite sheet name and sets the sprites accordingly
			std::string spritesheetName = "";
			int offset = 1;
			for (int j = tmx.tilesetList.size() - 1; j >= 0; --j) {
				if (texID < tmx.tilesetList[j].firstGID) continue;

				std::string tsxName = tmx.tilesetList[j].source;
				offset = tmx.tilesetList[j].firstGID;
				TSX::Parser tileSet = tileSets[tsxName];

				std::string imgSource = tileSet.tileset.image.source;

				size_t slashPos = imgSource.find_last_of("/");
				imgSource = imgSource.substr(slashPos + 1);

				size_t dotPos = imgSource.find(".");
				imgSource = imgSource.erase(dotPos, 4);

				spritesheetName = imgSource;

				trueID = texID - offset;

				for (int k = 0; k < tileSet.tileList.size(); k++) {
					if (tileSet.tileList[k].id == trueID) {
						if (tileSet.tileList[k]._collidable) {
							_collidableTileArray[i] = true;
						}

						if (tileSet.tileList[k]._hasAnimations) {
							_tileArr[currentLayer][i].animatedTileIDs = tileSet.tileList[k]._animatedTileID;
							_animatedTileArr.emplace_back(&_tileArr[currentLayer][i]);
						}
					}
				}

				break;
			}

			//Set the spritesheet and sprite 
			_tileArr[currentLayer][i]._pSpritesheet = ResourceManager::GetSpriteSheet(spritesheetName);
			_tileArr[currentLayer][i]._pSprite = ResourceManager::GetSpriteSheet(spritesheetName)->GetSpriteAtIndex(trueID);

			//Calculate the Y and X index of the tile
			int yIndex = i / _mapInTiles.x;
			int xIndex = i - (yIndex * _mapInTiles.x);

			//Calculate the tile position
			float xPos = (float)xIndex * _gapBetweenTiles;
			float yPos = ((float)yIndex * _gapBetweenTiles);

			float newYPos = _mapSizeInUnits.y - yPos;

			_tileArr[currentLayer][i].pos = { xPos, yPos };
			_tileArr[currentLayer][i].size = _gapBetweenTiles;
		}

		currentLayer++;
	}

	for (int layer = 0; layer < noOfLayers; layer++) {
		RendererData data = Renderer2D::GenerateRendererData();

		for (int i = 0; i < dimensions; i++) {
			TileData& td = _tileArr[layer][i];
			glm::vec2 pos = td.pos;

			if (td._pSprite == nullptr) continue;

			Renderer2D::AddData(data, Quad{ { pos.x, pos.y}, {_gapBetweenTiles, _gapBetweenTiles} }, td._pSprite->GetTexture(), td._pSprite->GetTexCoords());
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
	if (index > _mapInTiles.x* _mapInTiles.y) index = _mapInTiles.x * _mapInTiles.y;

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
	if (index > _mapInTiles.x* _mapInTiles.y) index = (_mapInTiles.x * _mapInTiles.y) - 1;

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
	_mapAnimationTimer += Time::GetDeltaTime();
	if (_mapAnimationTimer > _mapAnimationDuration) {
		_mapAnimationTimer = 0.0f;
		for (int i = 0; i < _animatedTileArr.size(); i++) {
			TileData* pCurrentTile = _animatedTileArr[i];

			pCurrentTile->animationIndex = (pCurrentTile->animationIndex + 1) % pCurrentTile->animatedTileIDs.size();

			//Convert position to a single dimension index.
			int index = GetTileIndexFromPosition(_animatedTileArr[i]->pos);

			//Multiply index by 4 so it is quad vertex space
			index *= 4;

			//Loops through each layer of render data
			for (int j = 0; j < _tilemapRendererData.size(); ++j) {
				//Sets the light level on the four different vertices of the quad.
				glm::vec2* texCoords = pCurrentTile->_pSpritesheet->GetSpriteAtIndex(pCurrentTile->animatedTileIDs[pCurrentTile->animationIndex])->GetTexCoords();

				_tilemapRendererData[j].quadVertexBufferBase[index].texCoord = texCoords[0];
				_tilemapRendererData[j].quadVertexBufferBase[index + 1].texCoord = texCoords[1];
				_tilemapRendererData[j].quadVertexBufferBase[index + 2].texCoord = texCoords[2];
				_tilemapRendererData[j].quadVertexBufferBase[index + 3].texCoord = texCoords[3];
			}
		}

		UpdateRenderInfo();
	}

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

