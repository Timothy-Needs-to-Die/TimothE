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

	_tilesPerUnit = 4;
	_gapBetweenTiles = 1.0f / _tilesPerUnit;

	LoadTileMap();
}

TileMap::~TileMap()
{
}

void TileMap::LoadTileMap()
{
	TMX::Parser tmx("Resources/Tilemaps/ArtTestMap.tmx");

	SetTileMapSize({ tmx.mapInfo.width, tmx.mapInfo.height });

	//Load Tilesets
	std::unordered_map<std::string, TSX::Parser> tileSets;
	for (int i = 0; i < tmx.tilesetList.size(); ++i) {
		std::string name = tmx.tilesetList[i].source;
		TSX::Parser tileset;
		tileset.load(("Resources/Tilemaps/" + name).c_str());
		tileSets.insert(std::make_pair(name, tileset));
	}

	//Load Objects
	for (std::map<std::string, TMX::Parser::ObjectGroup>::iterator it = tmx.objectGroup.begin(); it != tmx.objectGroup.end(); ++it) {
		_objectGroups.insert(std::make_pair(it->first, it->second));
	}


	//Get the number of layers
	_numLayers = tmx.tileLayer.size();
	int currentLayer = 0;

	//Iterate through each layer of the tilemap
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

				int index = y * _mapInTiles.x + x;
				int texID = std::stoi(results[index]);



				int trueY = (_mapInTiles.y - 1) - y;

				//Reads in the sprite sheet name and sets the sprites accordingly

				if (texID != 0) {
					int trueID = texID;
					std::string spritesheetName = "";

					//Loop through each tileset
					for (int j = tmx.tilesetList.size() - 1; j >= 0; --j) {
						//Check we are in range of this tilesets ids
						if (texID < tmx.tilesetList[j].firstGID - 1) continue;

						//Get the name of the source for this tileset
						std::string tsxName = tmx.tilesetList[j].source;

						//Gets the tileset from the stored sets
						TSX::Parser tileSet = tileSets[tsxName];
						std::string imgSource = tileSet.tileset.image.source;

						size_t slashPos = imgSource.find_last_of("/");
						imgSource = imgSource.substr(slashPos + 1);

						size_t dotPos = imgSource.find(".");
						imgSource = imgSource.erase(dotPos, 4);

						spritesheetName = imgSource;

						int offset = tmx.tilesetList[j].firstGID;
						trueID = texID - offset;

						for (int k = 0; k < tileSet.tileList.size(); k++) {
							if (tileSet.tileList[k].id == trueID) {
								if (tileSet.tileList[k]._collidable) {
									int tDex = (trueY * _mapInTiles.y + x);
									_collidableTileArray[trueY][x] = true;
								}

								if (tileSet.tileList[k]._hasAnimations) {
									for (int a = 0; a < tileSet.tileList[k]._animatedTileID.size(); a++) {
										unsigned int ID = tileSet.tileList[k]._animatedTileID[a];

										int noOfSprites = tileSet.tileset.noOfTiles;
										int sheetWidth = tileSet.tileset.columns;
										int sheetHeight = tileSet.tileset.rows;

										int yIndex = ID / sheetWidth;
										int xIndex = ID - (yIndex * sheetWidth);

										yIndex = (sheetHeight - 1) - yIndex;

										ID = yIndex * sheetWidth + xIndex;

										_tileArr[currentLayer][trueY][x]->animatedTileIDs.emplace_back(ID);
									}

									_animatedTileArr.emplace_back(_tileArr[currentLayer][trueY][x]);
								}
							}
						}

						break;
					}

					//Set the spritesheet and sprite 
					_tileArr[currentLayer][trueY][x]->_pSpritesheet = ResourceManager::GetSpriteSheet(spritesheetName);

					int noOfSprites = _tileArr[currentLayer][trueY][x]->_pSpritesheet->GetNumberOfSprites();
					int sheetWidth = _tileArr[currentLayer][trueY][x]->_pSpritesheet->GetSheetWidth();
					int sheetHeight = _tileArr[currentLayer][trueY][x]->_pSpritesheet->GetSheetHeight();

					int yIndex = trueID / sheetWidth;
					int xIndex = trueID - (yIndex * sheetWidth);

					yIndex = (sheetHeight - 1) - yIndex;

					trueID = yIndex * sheetWidth + xIndex;

					_tileArr[currentLayer][trueY][x]->_pSprite = ResourceManager::GetSpriteSheet(spritesheetName)->GetSpriteAtIndex(trueID);
				}

				//Calculate the tile position
				float xPos = (float)x * _gapBetweenTiles;
				float yPos = ((float)trueY * _gapBetweenTiles);

				_tileArr[currentLayer][trueY][x]->pos = { xPos, yPos };
				_tileArr[currentLayer][trueY][x]->size = _gapBetweenTiles;
			}
		}

		currentLayer++;
	}

	//Prepare the render data for the tilemap.
	for (int layer = 0; layer < _numLayers; layer++) {
		RendererData data = Renderer2D::GenerateRendererData();

		for (int y = 0; y < _mapInTiles.y; y++) {
			for (int x = 0; x < _mapInTiles.x; x++) {
				TileData* td = _tileArr[layer][y][x];
				glm::vec2 pos = td->pos;

				if (td->_pSprite == nullptr) continue;

				Renderer2D::AddData(data, Quad{ { pos.x, pos.y}, {_gapBetweenTiles, _gapBetweenTiles} }, td->_pSprite->GetTexture(), td->_pSprite->GetTexCoords());
			}
		}
		_tilemapRendererData.emplace_back(data);
	}


	//Find Player Spawn object and set the player spawn variable
	TMX::Parser::Object playerSpawn = GetObjectByName("PlayerSpawn");
	if (playerSpawn.name == "PlayerSpawn") {
		float xPos = playerSpawn.x;
		float yPos = (tmx.mapInfo.height * tmx.mapInfo.tileHeight) - playerSpawn.y;

		xPos /= (float)TILE_SIZE_IN_PIXELS;
		yPos /= (float)TILE_SIZE_IN_PIXELS;

		xPos *= _gapBetweenTiles;
		yPos *= _gapBetweenTiles;

		_playerSpawn = GetTileAtWorldPos(0, { xPos, yPos })->pos;

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

	for (int layer = 0; layer < _tileArr.size(); layer++) {
		_tileArr[layer].resize(_mapInTiles.y);

		for (int y = 0; y < _mapInTiles.y; y++) {
			_tileArr[layer][y].resize(_mapInTiles.x);

			for (int z = 0; z < _tileArr[layer][y].size(); z++) {
				_tileArr[layer][y][z] = new TileData();
			}
		}
	}

	_collidableTileArray = new bool* [_mapInTiles.y];
	for (int y = 0; y < _mapInTiles.y; y++) {
		_collidableTileArray[y] = new bool[_mapInTiles.x];
		memset(_collidableTileArray[y], false, _mapInTiles.x);
	}

	_lightLevelArray = new int[(int)mapSize.x * (int)mapSize.y];
	for (int i = 0; i < mapSize.x * mapSize.y; ++i) {
		_lightLevelArray[i] = 5;
	}


	_mapSizeInUnits = glm::vec2(_mapInTiles.x / _tilesPerUnit, _mapInTiles.y / _tilesPerUnit);
}

TileData* TileMap::GetTileAtWorldPos(int layer, glm::vec2 worldPos)
{
	if (worldPos.y < 0.0f) worldPos.y = 0.0f;
	else if (worldPos.y > _mapSizeInUnits.y) worldPos.y = _mapSizeInUnits.y;

	if (worldPos.x < 0.0f) worldPos.x = 0.0f;
	else if (worldPos.x >= _mapSizeInUnits.x) worldPos.x = _mapSizeInUnits.x - _gapBetweenTiles;

	int index = GetTileIndexFromPosition(worldPos);

	//Calculates the index of the tile

	//Protection in case specified position results in a tile outside of the map
	if (index < 0) index = 0;
	if (index >= _mapInTiles.x * _mapInTiles.y) index = (_mapInTiles.x * _mapInTiles.y) - 1;

	int yIndex = index / _mapInTiles.x;
	int xIndex = index - (yIndex * _mapInTiles.x);

	//Gets the tile on the specified layer
	return _tileArr[layer][yIndex][xIndex];
}

void TileMap::RenderMap(Camera* cam)
{
	//Increments the animation timer
	_mapAnimationTimer += Time::GetDeltaTime();
	//If the timer is greater than the duration
	if (_mapAnimationTimer > _mapAnimationDuration) {
		//Reset the timer
		_mapAnimationTimer = 0.0f;

		//Cycle through each animated tile and update the texture coords for it
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

	//Renders each layer as it's own draw call
	for (int i = 0; i < _tilemapRendererData.size(); i++) {
		//Gets a reference to the current renderer data.
		RendererData& data = _tilemapRendererData[i];

		//Updates the cameras position in the shader
		data.textureShader->SetMat4("view", cam->ViewProj());

		if (data.quadIndexCount != 0) {
			//Sets the data for each quad vertex
			uint32_t dataSize = (uint32_t)((uint8_t*)data.quadVertexBufferPtr - (uint8_t*)data.quadVertexBufferBase);
			data.quadVertexBuffer->SetData(data.quadVertexBufferBase, dataSize);

			//Binds all textures
			for (unsigned int i = 0; i < data.textureSlotIndex; i++) {
				data.textureSlots[i]->Bind(i);
			}

			//Binds the shader attached currently
			data.textureShader->BindShader();

			//Draws all the render data for the tilemap
			Renderer2D::DrawIndexed(data.quadVertexArray, data.quadIndexCount);
		}
	}
}

bool TileMap::CollidableAtPosition(glm::vec2 worldPos)
{
	//Gets the tile at this correct position. Ensures we are working with correct units
	TileData* td = GetTileAtWorldPos(0, worldPos);

	//Finds the row and column for this world position
	int row = worldPos.y / _gapBetweenTiles;
	int column = worldPos.x / _gapBetweenTiles;

	if (row < 0) row = 0;
	else if (row >= _mapInTiles.y) row = _mapInTiles.y - 1;

	if (column < 0) column = 0;
	else if (column >= _mapInTiles.x) column = _mapInTiles.x - 1;

	return CollidableAtIndexXY(row, column);
}


bool TileMap::CollidableAtIndexXY(int x, int y)
{
	return _collidableTileArray[x][y];
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
	//Cycles through all the renderer data
	for (int i = 0; i < _tilemapRendererData.size(); ++i) {
		//Calculates the data size
		uint32_t dataSize = (uint32_t)((uint8_t*)_tilemapRendererData[i].quadVertexBufferPtr - (uint8_t*)_tilemapRendererData[i].quadVertexBufferBase);

		//Sets the data in the vertex buffer to be the correct information
		_tilemapRendererData[i].quadVertexBuffer->SetData(_tilemapRendererData[i].quadVertexBufferBase, dataSize);
	}
}

void TileMap::SetCollidableAtPosition(glm::vec2 pos, bool val)
{
	//Calculate the row  and column to find the correct tile
	int row = pos.y / _gapBetweenTiles;
	int column = pos.x / _gapBetweenTiles;

	_collidableTileArray[row][column] = val;
}

int TileMap::GetTileIndexFromPosition(glm::vec2 pos)
{
	return  _mapInTiles.x * (int)(pos.y * _tilesPerUnit) + (int)(pos.x * _tilesPerUnit);
}

bool TileMap::CollidableAtIndex(int index) const
{
	if (index < 0 || index > _tileArr[0].size()) return false;

	return _collidableTileArray[index];
}

void TileMap::SetAllTilesLightLevel(int level)
{
	//Cycle through each tile in the tilemap
	for (int y = 0; y < _mapInTiles.y; y++) {
		for (int x = 0; x < _mapInTiles.x; x++) {
			//Set the light level of each tile to the desired value
			UpdateLightLevelAtPosition(_tileArr[0][y][x]->pos, level);
		}
	}

	//Updates the VAO and VBO for the tilemap
	UpdateRenderInfo();
}


struct RoomDetails {
	int xPos;
	int yPos;
	int xSize;
	int ySize;
};

bool CompareRoomX(RoomDetails& a, RoomDetails& b) {
	return a.xPos < b.xPos;
}

int*** TileMap::GenerateTileMap(int noOfRooms, int width /*= 64*/, int height /*= 64*/, int seed /*= -1*/)
{
	if (seed == -1) {
		srand(time(NULL));
	}
	else {
		srand(seed);
	}

	//3 Layers
	_numLayers = 3;
	int*** tilemap = new int** [3];

	for (int layer = 0; layer < 3; layer++) {
		tilemap[layer] = new int* [height];
		for (int i = 0; i < height; i++) {
			tilemap[layer][i] = new int[width];
			for (int x = 0; x < width; x++) {
				tilemap[layer][i][x] = 0;
			}
		}
	}


	std::vector<RoomDetails> rooms;



	//Pass 1: Find room placements
	for (int i = 0; i < noOfRooms; i++) {
		bool successful = false;
		while (!successful) {

			int randX = rand() % width;
			int randY = rand() % height;
			int sizeX = rand() % 12 + 4;
			int sizeY = rand() % 12 + 4;

			if (randX + sizeX + 2 > width - 1) {
				continue;
			}
			if (randY + sizeY + 2 > height - 1) {
				continue;
			}

			bool failed = false;
			for (int yTest = randY; yTest < randY + sizeY + 2; yTest++) {
				for (int xTest = randX; xTest < randX + sizeX + 2; xTest++) {
					if (tilemap[0][yTest][xTest] == 1) {
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
				RoomDetails roomInfo;

				roomInfo.xPos = randX;
				roomInfo.yPos = randY;
				roomInfo.xSize = sizeX;
				roomInfo.ySize = sizeY;


				for (int yTest = randY; yTest < randY + sizeY; yTest++) {
					for (int xTest = randX; xTest < randX + sizeX; xTest++) {
						tilemap[0][yTest][xTest] = 1;
					}
				}

				rooms.emplace_back(roomInfo);
			}

		}
	}

	std::sort(rooms.begin(), rooms.end(), CompareRoomX);

	//Pass 2: Connect rooms from left to right

	for (int i = 0; i < rooms.size() - 1; i++) {
		RoomDetails& a = rooms[i];
		RoomDetails& b = rooms[i + 1];

		int xStart = a.xPos + (rand() % a.xSize + 1) - 1;
		int yStart = a.yPos + (rand() % a.ySize + 1) - 1;

		int xEnd = b.xPos + (rand() % b.xSize + 1) - 1;
		int yEnd = b.yPos + (rand() % b.ySize + 1) - 1;

		int x = xStart;
		int y = yStart;

		while (x != xEnd || y != yEnd)
		{
			if (x < xEnd) {
				x += 1;
			}
			else if (x > xEnd) {
				x -= 1;
			}
			else if (y < yEnd) {
				y += 1;
			}
			else if (y > yEnd) {
				y -= 1;
			}

			tilemap[0][y][x] = 1;
		}
	}

	//Player Spawn
	int room1xStart = rooms[0].xPos;
	int room1yStart = rooms[0].yPos;
	int room1xEnd = rooms[0].xPos + rooms[0].xSize;
	int room1yEnd = rooms[0].yPos + rooms[0].ySize;

	int playerSpawnX = rand() % (room1xStart + 1) + (room1xEnd - 1);
	int playerSpawnY = rand() % (room1yStart + 1) + (room1yEnd - 1);

	tilemap[2][playerSpawnY][playerSpawnX] = 3;



	//Debug Test (Print map to screen)
	//for (int y = 0; y < height; y++) {
	//	for (int x = 0; x < width; x++) {
	//		std::cout << tilemap[y][x] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	return tilemap;
}

int TileMap::GetLightLevelAtPosition(glm::vec2 pos)
{
	//Gets the of the tile at the passed in world position and finds it's light value
	return _lightLevelArray[GetTileIndexFromPosition(pos)];
}

TMX::Parser::Object TileMap::GetObjectByName(std::string name) const
{
	//Cylce through all object groups
	for (auto og : _objectGroups) {
		//Cylce through all objects in that group
		for (auto o : og.second.object) {
			//if the name matches the desired name then return that object
			if (o.second.name == name) {
				return o.second;
			}
		}
	}

	//Catch condition for if we do not have the desired object
	return TMX::Parser::Object();
}

TMX::Parser::Object TileMap::GetObjectByNameInGroup(std::string groupName, std::string name) const
{
	//Search for the desired group
	auto it = _objectGroups.find(groupName);
	if (it != _objectGroups.end()) {
		//if the group exists, then cycle through all objects in it
		for (auto o : it->second.object) {
			//checks this objects name against the one we are searching for
			if (o.second.name == name) {
				return o.second;
			}
		}
	}

	//Catch condition for if we do not have the desired object
	return TMX::Parser::Object();
}

TMX::Parser::ObjectGroup TileMap::GetObjectGroupByName(std::string groupName) const
{
	//See if we have a object group with the desired name
	auto it = _objectGroups.find(groupName);
	if (it != _objectGroups.end()) {
		//if we have a object group with the desired name then return it
		return it->second;
	}

	//Catch condition for if we do not have the desired object group
	return TMX::Parser::ObjectGroup();
}

void TileMap::CreateTilemapFromProcGen(int*** map, int width, int height, std::string spritesheetName)
{
	//Resize the tile map array to the right size
	//Change the tile data to be what the tile is.
	//Establish standard for the tile layout on the tilesheet

	_animatedTileArr.clear();

	SpriteSheet* pSpriteSheet = ResourceManager::GetSpriteSheet(spritesheetName);

	_tilemapRendererData.clear();

	_tileArr.clear();
	_tileArr.resize(_numLayers);

	SetTileMapSize({ width, height });


	//Set all layers tile details
	for (int layer = 0; layer < _numLayers; layer++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int mapIndex = y * width + x;

				int value = map[0][y][x];

				int rVal = 0;
				int bVal = 0;
				int rbVal = 0;

				if (y < height - 2) {
					bVal = map[0][y + 1][x];

					if (x < width - 2) {
						rbVal = map[0][y + 1][x + 1];
					}
				}

				if (x < width - 2) {
					rVal = map[0][y][x + 1];
				}

				TileData* data = new TileData();

				data->animated = false;
				data->size = _gapBetweenTiles;

				data->pos = { x * _gapBetweenTiles, y * _gapBetweenTiles };
				data->_pSpritesheet = pSpriteSheet;
				_tileArr[0][y][x] = data;
			}
		}
	}

	//Background Pass
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int mapIndex = y * width + x;

			int value = map[0][y][x];

			int rVal = 0;
			int bVal = 0;
			int rbVal = 0;

			if (y < height - 2) {
				bVal = map[0][y + 1][x];

				if (x < width - 2) {
					rbVal = map[0][y + 1][x + 1];
				}
			}

			if (x < width - 2) {
				rVal = map[0][y][x + 1];
			}

			TileData* data = _tileArr[0][y][x];

			int texIndex = -1;

			std::string values;
			values = std::to_string(value) + std::to_string(rVal) + std::to_string(bVal) + std::to_string(rbVal);

			if (values == "0000") { //BLANK TILE
				_collidableTileArray[y][x] = true;
			}
			else if (values == "0001") { //TOP LEFT
				texIndex = (int)ProcTileMapValues::TOP_LEFT;
			}
			else if (values == "0011") { //TOP MIDDLE
				texIndex = (int)ProcTileMapValues::TOP_MIDDLE;
			}
			else if (values == "0010") { //TOP RIGHT
				texIndex = (int)ProcTileMapValues::TOP_RIGHT;
			}
			else if (values == "0101") { //MIDDLE LEFT
				texIndex = (int)ProcTileMapValues::MIDDLE_LEFT;
			}
			else if (values == "1111") { //MIDDLE MIDDLE / FLOOR
				texIndex = (int)ProcTileMapValues::MIDDLE_MIDDLE;
			}
			else if (values == "1010") { //MIDDLE RIGHT
				texIndex = (int)ProcTileMapValues::MIDDLE_RIGHT;
			}
			else if (values == "0100") { //BOTTOM LEFT
				texIndex = (int)ProcTileMapValues::BOTTOM_LEFT;
			}
			else if (values == "1100") { //BOTTOM MIDDLE
				texIndex = (int)ProcTileMapValues::BOTTOM_MIDDLE;
			}
			else if (values == "1000") { //BOTTOM RIGHT
				texIndex = (int)ProcTileMapValues::BOTTOM_RIGHT;
			}
			else if (values == "1011") {
				texIndex = (int)ProcTileMapValues::INTERIOR_BOTTOM_LEFT;
			}
			else if (values == "0111") {
				texIndex = (int)ProcTileMapValues::INTERIOR_BOTTOM_RIGHT;
			}
			else if (values == "1110") {
				texIndex = (int)ProcTileMapValues::INTERIOR_TOP_LEFT;
			}
			else if (values == "1101") {
				texIndex = (int)ProcTileMapValues::INTERIOR_TOP_RIGHT;
			}


			data->texIndex = texIndex;
			if (texIndex != -1) {
				data->texIndex = texIndex;
				data->_pSprite = data->_pSpritesheet->GetSpriteAtIndex(texIndex);
			}
		}

	}


	//Decoration Layer


	//Interactive Layer
	int psX = 0;
	int psY = 0;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[2][y][x] == 3) {
				psX = x;
				psY = y;
			}
		}
	}

	//Player Spawn
	_playerSpawn = _tileArr[2][psY][psX]->pos;




	//Level End



	for (int layer = 0; layer < _numLayers; layer++) {
		RendererData data = Renderer2D::GenerateRendererData();

		for (int y = 0; y < _mapInTiles.y; y++) {
			for (int x = 0; x < _mapInTiles.x; x++) {
				TileData* td = _tileArr[layer][y][x];
				glm::vec2 pos = td->pos;

				if (td->texIndex == -1) continue;
				if (td->_pSprite == nullptr) continue;

				Renderer2D::AddData(data, Quad{ { pos.x, pos.y}, {_gapBetweenTiles, _gapBetweenTiles} }, td->_pSprite->GetTexture(), td->_pSprite->GetTexCoords());
			}
		}
		_tilemapRendererData.emplace_back(data);
	}

	UpdateRenderInfo();
}

