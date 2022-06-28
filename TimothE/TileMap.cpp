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


		for (int y = _mapInTiles.y - 1; y >= 0; y--) {
			for (int x = 0; x < _mapInTiles.x; x++) {
				int index = y * _mapInTiles.y + x;
				int texID = std::stoi(results[index]);
				int trueID = texID;

				int trueY = (_mapInTiles.y - 1) - y;

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
								int tDex = trueY * _mapInTiles.y + x;
								_collidableTileArray[tDex] = true;
							}

							if (tileSet.tileList[k]._hasAnimations) {
								for (int a = 0; a < tileSet.tileList[k]._animatedTileID.size(); a++) {
									unsigned int ID = tileSet.tileList[k]._animatedTileID[a];

									//tileSet.tileset.tileWidth

									int noOfSprites = tileSet.tileset.noOfTiles;
									int sheetWidth = tileSet.tileset.columns;
									int sheetHeight = tileSet.tileset.rows;

									int yIndex = ID / sheetWidth;
									int xIndex = ID - (yIndex * sheetWidth);

									yIndex = (sheetHeight - 1) - yIndex;

									ID = yIndex * sheetWidth + xIndex;

									_tileArr[currentLayer][trueY][x].animatedTileIDs.emplace_back(ID);
								}

								_animatedTileArr.emplace_back(&_tileArr[currentLayer][trueY][x]);
							}
						}
					}

					break;
				}

				//Set the spritesheet and sprite 
				_tileArr[currentLayer][trueY][x]._pSpritesheet = ResourceManager::GetSpriteSheet(spritesheetName);

				int noOfSprites = _tileArr[currentLayer][trueY][x]._pSpritesheet->GetNumberOfSprites();
				int sheetWidth = _tileArr[currentLayer][trueY][x]._pSpritesheet->GetSheetWidth();
				int sheetHeight = _tileArr[currentLayer][trueY][x]._pSpritesheet->GetSheetHeight();

				int yIndex = trueID / sheetWidth;
				int xIndex = trueID - (yIndex * sheetWidth);

				yIndex = (sheetHeight - 1) - yIndex;

				trueID = yIndex * sheetWidth + xIndex;

				_tileArr[currentLayer][trueY][x]._pSprite = ResourceManager::GetSpriteSheet(spritesheetName)->GetSpriteAtIndex(trueID);


				//Calculate the tile position
				float xPos = (float)x * _gapBetweenTiles;
				float yPos = ((float)trueY * _gapBetweenTiles);

				_tileArr[currentLayer][trueY][x].pos = { xPos, yPos };
				_tileArr[currentLayer][trueY][x].size = _gapBetweenTiles;
			}
		}

		currentLayer++;
	}

	for (int layer = 0; layer < noOfLayers; layer++) {
		RendererData data = Renderer2D::GenerateRendererData();

		for (int y = 0; y < _mapInTiles.y; y++) {
			for (int x = 0; x < _mapInTiles.x; x++) {
				TileData& td = _tileArr[layer][y][x];
				glm::vec2 pos = td.pos;

				if (td._pSprite == nullptr) continue;

				Renderer2D::AddData(data, Quad{ { pos.x, pos.y}, {_gapBetweenTiles, _gapBetweenTiles} }, td._pSprite->GetTexture(), td._pSprite->GetTexCoords());
			}
		}
		_tilemapRendererData.emplace_back(data);
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
		_tileArr[i].resize(_mapInTiles.y);

		for (int y = 0; y < _mapInTiles.y; y++) {
			_tileArr[i][y].resize(_mapInTiles.x);
		}
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

	int yIndex = index / _mapInTiles.x;
	int xIndex = index - (yIndex * _mapInTiles.x);

	//Gets the tile on the specified layer
	return &_tileArr[layer][yIndex][xIndex];
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
	for (int y = 0; y < _mapInTiles.y; y++) {
		for (int x = 0; x < _mapInTiles.x; x++) {
			UpdateLightLevelAtPosition(_tileArr[0][y][x].pos, level);
		}
	}


	for (int i = 0; i < _mapInTiles.x * _mapInTiles.y; ++i) {
	}

	UpdateRenderInfo();
}


void TileMap::GenerateTileMap(int noOfRooms, int width /*= 64*/, int height /*= 64*/, int seed /*= -1*/)
{
	if (seed == -1) {
		srand(time(NULL));
	}
	else {
		srand(seed);
	}

	int** tilemap = new int* [height];
	
	for (int i = 0; i < height; i++) {
		tilemap[i] = new int[width];
		memset(tilemap[i], 0, width);
		
	}


	//Pass 1: Find room placements
	for (int i = 0; i < noOfRooms; i++) {
		bool successful = false;
		while (!successful) {
			
			int randX = rand() % width;
			int randY = rand() % height;
			int sizeX = rand() % 12 + 4;
			int sizeY = rand() % 12 + 4;

			if (randX + sizeX > width - 1) {
				continue;
			}
			if (randY + sizeY > height - 1) {
				continue;
			}
			
			bool failed = false;
			for (int yTest = randY; yTest < randY + sizeY + 2; yTest++) {
				if (yTest >= height) {
					failed = true;
					continue;
				}

				for (int xTest = randX; xTest < randX + sizeX + 2; xTest++) {
					if (xTest >= width) {
						failed = true;
						continue;
					}

					if (tilemap[yTest][xTest] == 1) {
						failed = true;
						break;
					}
				}
			}


			if (failed) {
				continue;
			}

			successful = true;

			if (successful) {
				for (int yTest = randY; yTest < randY + sizeY; yTest++) {
					for (int xTest = randX; xTest < randX + sizeX; xTest++) {
						tilemap[yTest][xTest] = 1;
					}
					if (!successful) break;
				}
			}
		}
	}


	//Pass 2: Connect rooms from left to right


	//Debug Test (Print map to screen)
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << tilemap[y][x] << " ";
		}
		std::cout << std::endl;
	}

}

int TileMap::GetLightLevelAtPosition(glm::vec2 pos)
{
	int index = GetTileIndexFromPosition(pos);
	return _lightLevelArray[index];
}

