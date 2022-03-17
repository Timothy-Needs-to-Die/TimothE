#include "TileMapEditor.h"


bool TileMapEditor::_hasTileData = false;
bool TileMapEditor::_isActive = false;
std::string TileMapEditor::_mapName = "testSheet.png";
std::string TileMapEditor::_textureName = "spritesheet";
glm::vec2 TileMapEditor::_mapSizeInScreenUnits = glm::vec2(32.0);
glm::vec2 TileMapEditor::_tileSize = glm::vec2(32.0);
std::string TileMapEditor::_name;
SelectedTile TileMapEditor::_selectedTile;

void TileMapEditor::EnableEditor()
{
	_isActive = true;
}

void TileMapEditor::Update(TileMap* pTilemap)
{
	if (!_isActive)
		return;
	if (!_hasTileData)
		AcquireData(pTilemap);
	else
		CreateTileMap(pTilemap);

	pTilemap->UpdateLogic(CameraManager::CurrentCamera());
}

void TileMapEditor::AcquireData(TileMap* pTilemap)
{
	static char infoName[50];
	ImGui::Begin("Tile Map Info", 0, ImGuiWindowFlags_NoMove);
	ImGui::InputText("Tile Map Name", infoName, 50);
	ImGui::InputFloat("Tile count X", &_mapSizeInScreenUnits.x);
	ImGui::InputFloat("Tile Count Y", &_mapSizeInScreenUnits.y);
	ImGui::InputFloat("Tile Size X", &_tileSize.x);
	ImGui::InputFloat("Tile Size Y", &_tileSize.y);
	ImGui::Text("Selected Texture Atlas: %s", _textureName.c_str());

	//TODO - Get a list of the loaded textures for the current map
	//for (const auto& x : /*GetTextureList() */)
	//{
	//	_textureName = x.first;
	//}



	ImGui::Separator();
	if (ImGui::Button("Start"))
	{
		if (_mapSizeInScreenUnits.x >= 1 && _mapSizeInScreenUnits.y >= 1 && _tileSize.x > 0 && _tileSize.y > 0 && !_textureName.empty() && infoName[0] != '\0')
		{
			_name = std::string(infoName);
			_hasTileData = true;
		}
	}

	if (ImGui::Button("Close"))
	{
		_hasTileData = false;
		_isActive = false;
	}
	ImGui::End();
}

//Sets the data in the tileMap object that the editor will be editing
//Along with setting up the ImGui window for the editor 
void TileMapEditor::CreateTileMap(TileMap* pTilemap)
{
	static bool gridLinesCreated = false;
	static bool spriteArrayCreated = false;

	int x = pTilemap->GetSpriteSheet()->GetSheetWidth();
	int y = pTilemap->GetSpriteSheet()->GetSheetHeight();

	//static VAO VERTEX ARRAY gridLines;
	//static std::vector<Sprite> sprites;
	static std::vector<Texture2D*> textures;
	static std::vector<bool>collidableInfo;

	static TileMap mapToCreate;
	static bool mapCreated = false;

	if (!mapCreated)
	{
		mapToCreate.SetTileSize(_tileSize);
		mapToCreate.SetPosition(0.0f, 0.0f);
		mapToCreate.SetTileMapSize(_mapSizeInScreenUnits);
		mapToCreate.SetMapName(_mapName);
		mapToCreate.SetTextureName(_textureName);
		mapToCreate.CreateNewLayer();
		mapCreated = true;
	}
	//if (!gridLinesCreated)
	//{
	//	gridLines.Clear();
	//	gridLines.SetPrimitiveType(Lines);
	//	for (auto i = 0; i <= _mapSize.x; i++) {
	//		//Append grid lines with vec2(i * _tileSize.x, 0.0f)
	//		//Append grid lines with vec2((i) * _tileSize.x, _tileSize.y * _mapSize.y)
	//	}
	//	
	//	for (auto i = 0; i <= _mapSize.x; i++) {
	//		//Append grid lines with vec2(i * _tileSize.y, 0.0f)
	//		//Append grid lines with vec2(_tileSize.x, _mapSize.x, _tileSize.y * (i) )
	//	}
	//	gridLinesCreated = true;
	//}
	if (!spriteArrayCreated) {
		textures.clear();

		const auto& tex = ResourceManager::GetTexture("spritesheet");
		auto sizeX = tex->GetWidth();
		auto sizeY = tex->GetHeight();

		//x = sizeX / _tileSize.x;
		//y = sizeY / _tileSize.y;
		//for (auto i = 0; i < y; i++) {
		//	for (auto j = 0; j < x; j++) {
		//		//CREATE USEFUL SPRITE COMPONENT FOR This
		//		Sprite spr;
		//		spr.SetTexture(tex);
		//		spr.SetTextureRect(j * _tileSize.x, i * _tileSize.y, _tileSize.x, _tileSize.y);
		//		sprites.push_back(std::move(spr));
		//		collidableInfo.push_back(false);
		//	}
		//}
		//spriteArrayCreated = true;
	}


	float sheetWidth = (float)pTilemap->GetSpriteSheet()->GetPixelWidth();
	float sheetHeight = (float) pTilemap->GetSpriteSheet()->GetPixelHeight();
	float spriteWidth = (float)pTilemap->GetSpriteSheet()->GetSpriteWidth();
	float spriteHeight = (float)pTilemap->GetSpriteSheet()->GetSpriteHeight();

	const auto& tex = ResourceManager::GetTexture(_textureName);
	ImGui::Begin("Tilemap Editor", 0, ImGuiWindowFlags_NoMove);
	

	{
		ImGui::BeginChild("Select Tile", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 260));

		float imgDimensions = ImGui::GetWindowSize().x / spriteWidth;
		if (ImGui::BeginTable("split", 8)) {
			for (auto i = 0; i < y; i++)
			{
				for (auto j = 0; j < x; j++)
				{
					ImVec2 bl = ImVec2(((j)*spriteWidth) / sheetWidth, (i * spriteHeight) / sheetHeight);
					ImVec2 tr = ImVec2(((j + 1) * spriteWidth) / sheetWidth, ((i + 1) * spriteHeight) / sheetHeight);


					ImGui::TableNextColumn();
					ImGui::PushID(i * x + j);
					if (ImGui::ImageButton((void*)tex->GetID(), ImVec2(32, 32), tr, bl))
					{
						_selectedTile.tileX = j;
						_selectedTile.tileY = i;
						std::cout << "Selected: " << i << ", " << j << std::endl;
						_selectedTile._tileIndex = i * x + j;
					}
					ImGui::PopID();
					//ImGui::SameLine();
				}
				ImGui::NewLine();
			}
		}
		ImGui::EndTable();

		ImGui::EndChild();
	}

	ImGui::SameLine();
	{
		ImGui::BeginChild("Tile Settings", ImVec2(0, 260));

		ImGui::NewLine();

		/*Collidable Toggle
		if (_selectedTile._tileIndex >= 0 && _selectedTile._tileIndex < sprites.size())
		{
			ImGui::Text("Tile %d Collidable?", _selectedTile._tileIndex);
			ImGui::SameLine();

			if (ImGui::Button("Yes"))
				collidableInfo[_selectedTile._tileIndex] = true;
			ImGui::SameLine();
			if (ImGui::Button("No"))
				collidableInfo[_selectedTile._tileIndex] = false;
		}*/

		//if (_selectedTile == nullptr) return;

		//Layer Selection
		ImGui::Separator();
		ImGui::Text("CurrentLayer: %d", _selectedTile.currentLayer);
		ImGui::Separator();
		//for (auto i = 0; i < mapToCreate.GetLayerCount(); i++)
		//{
		//	auto str = "Layer " + std::to_string(i);
		//	if (ImGui::Selectable(str.c_str()))
		//	{
		//		_selectedTile.currentLayer = i;
		//	}
		//}
		ImGui::Separator();

		if (ImGui::Button("Fill"))
		{
			if (_selectedTile._tileIndex >= 0)
			{
				mapToCreate.FillLayer(_selectedTile.currentLayer, _selectedTile._tileIndex);
			}
		}

		//Add Layer Button
		ImGui::SameLine();
		if (ImGui::Button("Add Layer"))
		{
			mapToCreate.CreateNewLayer();
		}

		//Clear Map Button
		ImGui::SameLine();
		if (ImGui::Button("Clear Map")) {
			mapToCreate.DeleteAllLayers();
			mapToCreate.CreateNewLayer();
			_selectedTile.currentLayer = 0;
		}

		ImGui::Separator();

		if (ImGui::Button("Save TileMap"))
		{
			SaveTileMap(mapToCreate, collidableInfo);
			_isActive = false;
			_hasTileData = false;
			mapCreated = false;
			gridLinesCreated = false;
			spriteArrayCreated = false;
			mapToCreate.Clear();
			collidableInfo.clear();

			_selectedTile.currentLayer = 0;
			_selectedTile._tileIndex = -1;
		}

		ImGui::Separator();
		if (ImGui::Button("Close")) {
			_isActive = false;
			_hasTileData = false;
			mapCreated = false;
			gridLinesCreated = false;
			spriteArrayCreated = false;
			mapToCreate.Clear();
			collidableInfo.clear();

			_selectedTile.currentLayer = 0;
			_selectedTile._tileIndex = -1;
		}

		ImGui::EndChild();
	}

	ImGui::Separator();




	ImGui::End();

	if (Input::IsMouseButtonDown(BUTTON_LEFT)) {
		pTilemap->AddTileAt(0, _selectedTile.tileX, _selectedTile.tileY, CameraManager::GetCamera("Editor"), true);
	}
	else if (Input::IsMouseButtonDown(BUTTON_RIGHT)) {
		pTilemap->AddTileAt(0, 0, 0, CameraManager::GetCamera("Editor"), false);
	}
}

void TileMapEditor::SaveTileMap(const TileMap& map, const std::vector<bool>& collisionInfo)
{
	using nlohmann::json;
	
	json root;

	auto layers = json::array();
	
	//for (const auto& layer : map.GetTileData())
	//{
	//	auto x = json::object();
	//	auto data = json::array();
	//	for (auto tileIndex : layer)
	//	{
	//		data.push_back(layer);
	//	}
	//	x["DATA"] = std::move(data);
	//	layers.push_back(x);
	//}
	//
	//auto col = json::object();
	//for (int i = 0; i < collisionInfo.size(); i++)
	//{
	//	col[std::to_string(i)] = collisionInfo[i];
	//}
	//
	//root["WIDTH"] = map.GetTileWidth();
	//root["HEIGHT"] = map.GetTileHeight();
	//
	//root["TILE_WIDTH"] = map.GetTileSize().x;
	//root["TILE_HEIGHT"] = map.GetTileSize().y;
	//
	//root["LAYERS"] = std::move(layers);
	//root["COLLIDABLE_INFO"] = collisionInfo;
	//root["TEXTURE_NAME"] = map.GetTextureName();
	//
	//std::ofstream fileToWrite(map.GetName() + ".json");
	//fileToWrite << root;
	//
	//std::cout << "Successfully saved tileMap to json file" << std::endl;
}
