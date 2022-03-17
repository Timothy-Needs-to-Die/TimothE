#include "TileMapEditor.h"


bool TileMapEditor::_collidableToggle = false;
std::string TileMapEditor::_mapName = "testSheet.png";
std::string TileMapEditor::_spritesheetName = "spritesheet";
glm::vec2 TileMapEditor::_mapSizeInScreenUnits = glm::vec2(32.0);
glm::vec2 TileMapEditor::_tileSize = glm::vec2(32.0);
std::string TileMapEditor::_name;
SelectedTile TileMapEditor::_selectedTile;
int TileMapEditor::_currentLayer = 0;

void TileMapEditor::Update(TileMap* pTilemap)
{
	CreateTileMap(pTilemap);

	pTilemap->UpdateLogic(CameraManager::CurrentCamera());
}

//Sets the data in the tileMap object that the editor will be editing
//Along with setting up the ImGui window for the editor 
void TileMapEditor::CreateTileMap(TileMap* pTilemap)
{



	//const auto& tex = ResourceManager::GetTexture(_spritesheetName);
	ImGui::Begin("Tilemap Editor", 0, ImGuiWindowFlags_NoMove);

	//Tile display
	{
		ImGui::BeginChild("Select Tile", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, ImGui::GetContentRegionAvail().y * 0.75f));

		if (pTilemap->GetSpriteSheet()) {
			//Furthest tile in X and Y axis'
			int xMax = pTilemap->GetSpriteSheet()->GetSheetWidth();
			int yMax = pTilemap->GetSpriteSheet()->GetSheetHeight();

			float sheetWidth = pTilemap->GetSpriteSheet()->GetPixelWidth();
			float sheetHeight = pTilemap->GetSpriteSheet()->GetPixelHeight();
			float spriteWidth = pTilemap->GetSpriteSheet()->GetSpriteWidth();
			float spriteHeight = pTilemap->GetSpriteSheet()->GetSpriteHeight();

			if (ImGui::BeginTable("split", 8)) {
				for (auto i = 0; i < yMax; i++)
				{
					for (auto j = 0; j < xMax; j++)
					{
						ImVec2 bl = ImVec2(((j + 1) * spriteWidth) / sheetWidth, (i * spriteHeight) / sheetHeight);
						ImVec2 tr = ImVec2(((j)*spriteWidth) / sheetWidth, ((i + 1) * spriteHeight) / sheetHeight);


						ImGui::TableNextColumn();
						ImGui::PushID(i * xMax + j);
						if (ImGui::ImageButton((void*)pTilemap->GetSpriteSheet()->GetTexture()->GetID(), ImVec2(32, 32), tr, bl))
						{
							_selectedTile.tileX = j;
							_selectedTile.tileY = i;
							std::cout << "Selected: " << i << ", " << j << std::endl;
						}
						ImGui::PopID();
						//ImGui::SameLine();
					}
					ImGui::NewLine();
				}

				ImGui::EndTable();
			}
		}
		
		ImGui::EndChild();
	}

	ImGui::SameLine();

	{
		ImGui::BeginChild("Tilemap Settings", ImVec2(0, ImGui::GetContentRegionAvail().y * 0.75f));

		ImGui::Text("Layer: ");
		ImGui::SameLine();
		ImGui::PushItemWidth(150.0f);
		ImGui::SliderInt("##", &_currentLayer, 0, 2);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Fill Layer"))
		{
			pTilemap->FillLayer(_currentLayer, _selectedTile.tileX, _selectedTile.tileY);
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear Current Layer")) {
			pTilemap->ClearLayer(_currentLayer);
		}

		ImGui::Separator();

		ImGui::Checkbox("Collidable: ", &_collidableToggle);

		if (ImGui::Button("Save TileMap"))
		{
			SaveTileMap(*pTilemap);
		}

		ImGui::Separator();

		//Clear Map Button
		if (ImGui::Button("Clear Map")) {
			pTilemap->ClearAllLayers();
		}

		ImGui::Separator();

		static char infoName[50];
		ImGui::InputText("Tile Map Name", infoName, 50);
		ImGui::InputFloat("Tile count X", &_mapSizeInScreenUnits.x);
		ImGui::InputFloat("Tile Count Y", &_mapSizeInScreenUnits.y);
		ImGui::InputFloat("Tile Size X", &_tileSize.x);
		ImGui::InputFloat("Tile Size Y", &_tileSize.y);
		static char spritesheetName[50];
		if (ImGui::InputText("Spritesheet Name: ", spritesheetName, 50));

		static bool _loadedSheet;

		if (ImGui::Button("Search for Sheet")) {

			std::string temp = spritesheetName;

			SpriteSheet* spritesheet = ResourceManager::GetSpriteSheet(temp);

			if (spritesheet) {
				_loadedSheet = true;
				_spritesheetName = spritesheetName;
				pTilemap->SetSpriteSheet(spritesheet);
			}
			else {
				_loadedSheet = false;
			}
		}

		if (_loadedSheet) {

		ImGui::Text("Selected Texture Atlas: %s", _spritesheetName.c_str());
		}
		else {
			ImGui::Text("Spritesheet could not be loaded: %s", spritesheetName);
		}

		ImGui::EndChild();
	}

	ImGui::Separator();

	ImGui::End();

	ImGui::Begin("Scene Window", 0, ImGuiWindowFlags_NoMove);

	if (ImGui::IsWindowFocused()) {
		if (Input::IsMouseButtonDown(BUTTON_LEFT)) {
			pTilemap->AddTileAt(_currentLayer, _selectedTile.tileX, _selectedTile.tileY, CameraManager::GetCamera("Editor"), _collidableToggle);
		}
		else if (Input::IsMouseButtonDown(BUTTON_RIGHT)) {
			pTilemap->AddTileAt(_currentLayer, 0, 0, CameraManager::GetCamera("Editor"), _collidableToggle);
		}
	}

	ImGui::End();
}

void TileMapEditor::SaveTileMap(const TileMap& map)
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
