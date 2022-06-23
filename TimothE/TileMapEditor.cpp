#include "pch.h"
#include "TileMapEditor.h"


bool TileMapEditor::_collidableToggle = false;
bool TileMapEditor::_showCollisionMap = false;
bool TileMapEditor::_active = false;

std::string TileMapEditor::_spritesheetName = "spritesheet";
glm::vec2 TileMapEditor::_mapSizeInUnits = glm::vec2(32.0);
SelectedTile TileMapEditor::_selectedTile;
int TileMapEditor::_currentLayer = 0;
SpriteSheet* TileMapEditor::_pCurrentSpritesheet;

void TileMapEditor::Update(TileMap* pTilemap)
{
	EditorUI(pTilemap);

}

//Sets the data in the tileMap object that the editor will be editing
//Along with setting up the ImGui window for the editor 
void TileMapEditor::EditorUI(TileMap* pTilemap)
{
	if (_pCurrentSpritesheet == nullptr) {
		_pCurrentSpritesheet = ResourceManager::GetSpriteSheet("testSheet");
	}

	//const auto& tex = ResourceManager::GetTexture(_spritesheetName);
	ImGui::Begin("Tilemap Editor", 0, ImGuiWindowFlags_NoMove);

	//Tile display
	{
		ImGui::BeginChild("Select Tile", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 400.0f));

		if (_pCurrentSpritesheet) {
			//Furthest tile in X and Y axis'
			int xMax = _pCurrentSpritesheet->GetSheetWidth();
			int yMax = _pCurrentSpritesheet->GetSheetHeight();

			float sheetWidth =		_pCurrentSpritesheet->GetPixelWidth();
			float sheetHeight =		_pCurrentSpritesheet->GetPixelHeight();
			float spriteWidth =		_pCurrentSpritesheet->GetSpriteWidth();
			float spriteHeight =	_pCurrentSpritesheet->GetSpriteHeight();

			if (ImGui::BeginTable("split", 8)) {
				for (auto i = 0; i < yMax; i++)
				{
					for (auto j = 0; j < xMax; j++)
					{
						ImVec2 bl = ImVec2(((j + 1) * spriteWidth) / sheetWidth, (i * spriteHeight) / sheetHeight);
						ImVec2 tr = ImVec2(((j)*spriteWidth) / sheetWidth, ((i + 1) * spriteHeight) / sheetHeight);


						ImGui::TableNextColumn();
						ImGui::PushID(i * xMax + j);
						if (ImGui::ImageButton((void*)_pCurrentSpritesheet->GetTexture()->GetID(), ImVec2(32, 32), tr, bl))
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

		ImGui::Text("Currently Editing: %s", pTilemap->GetName());

		ImGui::Text("Layer: ");
		ImGui::SameLine();
		ImGui::PushItemWidth(150.0f);
		ImGui::SliderInt("##", &_currentLayer, 0, 5);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Fill Layer"))
		{
			//pTilemap->FillLayer(_currentLayer, _selectedTile.tileX, _selectedTile.tileY, _pCurrentSpritesheet);
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear Current Layer")) {
			//pTilemap->ClearLayer(_currentLayer);
		}

		ImGui::Separator();

		ImGui::Checkbox("Collidable: ", &_collidableToggle);

		ImGui::Checkbox("Show Collision Map: ", &_showCollisionMap);

		if (ImGui::Button("Save TileMap"))
		{
		}

		ImGui::Separator();

		//Clear Map Button
		if (ImGui::Button("Clear Map")) {
			//pTilemap->ClearAllLayers();
		}

		ImGui::Separator();

		static bool _mapSizeChanged = false;
		_mapSizeChanged = false;

		ImGui::TextColored(ImVec4(1.0f, 0.0f,0.0f,1.0f), "Do not change after starting. It will not scale well");
		if (ImGui::InputFloat("Tile Count X", &_mapSizeInUnits.x)) _mapSizeChanged = true;
		if (ImGui::InputFloat("Tile Count Y", &_mapSizeInUnits.y)) _mapSizeChanged = true;

		if (_mapSizeChanged) {
			pTilemap->SetTileMapSize(_mapSizeInUnits);
		}

		static char spritesheetName[50];
		if (ImGui::InputText("Spritesheet Name: ", spritesheetName, 50));

		static bool _loadedSheet;

		if (ImGui::Button("Search for Sheet")) {

			std::string temp = spritesheetName;

			SpriteSheet* spritesheet = ResourceManager::GetSpriteSheet(temp);

			if (spritesheet) {
				_loadedSheet = true;
				_spritesheetName = spritesheetName;
				_pCurrentSpritesheet = spritesheet;
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
			//pTilemap->AddTileAt(_currentLayer, _selectedTile.tileX, _selectedTile.tileY, CameraManager::GetCamera("Editor"), _pCurrentSpritesheet, _collidableToggle);
		}
		else if (Input::IsMouseButtonDown(BUTTON_RIGHT)) {
			//pTilemap->AddTileAt(_currentLayer, 0, 0, CameraManager::GetCamera("Editor"), _pCurrentSpritesheet, _collidableToggle);
		}
	}
	ImGui::End();
}

