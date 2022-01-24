#include "TileMapEditor.h"

void TileMapEditor::EnableEditor()
{
	_isActive = true;
}

void TileMapEditor::DisplayEditorGUI(GLFWwindow* window)
{
	if (!_isActive)
		return;
	if (!_hasTileData)
		return;
	else
		CreateTileMap(window);
}

//Sets the data in the tileMap object that the editor will be editing
//Along with setting up the ImGui window for the editor 
void TileMapEditor::CreateTileMap(GLFWwindow* window)
{
	static bool gridLinesCreated = false;
	static bool spriteArrayCreated = false;

	static int x;
	static int y;

	//static VAO VERTEX ARRAY gridLines;
	static std::vector<Sprite> sprites;
	static std::vector<Texture2D*> textures;
	static std::vector<bool>collidableInfo;

	static TileMap mapToCreate;
	static bool mapCreated = false;

	if (!mapCreated)
	{
		mapToCreate.SetTileSize(_tileSize);
		mapToCreate.SetPosition(0.0f, 0.0f);
		mapToCreate.SetTileMapSize(_mapSize);
		mapToCreate.SetMapName(_mapName);
		mapToCreate.SetTextureName(_textureName);
		mapToCreate.CreateNewLayer();
		mapCreated = true;
	}
	if (!gridLinesCreated)
	{
		gridLines.Clear();
		gridLines.SetPrimitiveType(Lines);
		for (auto i = 0; i <= _mapSize.x; i++) {
			//Append grid lines with vec2(i * _tileSize.x, 0.0f)
			//Append grid lines with vec2((i) * _tileSize.x, _tileSize.y * _mapSize.y)
		}
		
		for (auto i = 0; i <= _mapSize.x; i++) {
			//Append grid lines with vec2(i * _tileSize.y, 0.0f)
			//Append grid lines with vec2(_tileSize.x, _mapSize.x, _tileSize.y * (i) )
		}
		gridLinesCreated = true;
	}
	if (!spriteArrayCreated) {
		textures.clear();

		const auto& tex = ResourceManager::GetTexture(_textureName);
		auto sizeX = tex.GetWidth();
		auto sizeY = tex.GetHeight();

		x = sizeX / _tileSize.x;
		y = sizeY / _tileSize.y;
		for (auto i = 0; i < y; i++) {
			for (auto j = 0; j < x; j++) {
				//CREATE USEFUL SPRITE COMPONENT FOR This
				Sprite spr;
				spr.SetTexture(tex);
				spr.SetTextureRect(j * _tileSize.x, i * _tileSize.y, _tileSize.x, _tileSize.y);
				sprites.push_back(std::move(spr));
				collidableInfo.push_back(false);
			}

		}
		spriteArrayCreated = true;

	}

	ImGui::Begin("Select Tile");
	for (auto i = 0; i < y; i++)
	{
		for (auto j = 0; j < x; j++)
		{
			auto& s = sprites[i * x + j];
			ImGui::PushID(i * x + j);
			if (ImGui::ImageButton(s))
			{
				_selectedTile.sprite = s;
				_selectedTile.sprite.SetColor(Colour(255, 255, 255, 128));
				_selectedTile._tileIndex = i * x + j;
			}
			ImGui::PopID();
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}

	ImGui::NewLine();

	//Collidable Toggle
	if (_selectedTile._tileIndex >= 0 && _selectedTile._tileIndex < sprites.size())
	{
		ImGui::Text("Tile %d Collidable?", _selectedTile._tileIndex);
		ImGui::SameLine();

		if (ImGui::Button("Yes"))
			collidableInfo[_selectedTile._tileIndex] = true;
		ImGui::SameLine();
		if (ImGui::Button("No"))
			collidableInfo[_selectedTile._tileIndex] = false;
	}

	//Layer Selection
	ImGui::Separator();
	ImGui::Text("CurrentLayer: %d", _selectedTile.currentLayer);
	ImGui::Separator();
	for (auto i = 0; i < mapToCreate.GetLayerCount(); i++)
	{
		auto str = "Layer " + std::to_string(i);
		if (ImGui::Selectable(str.c_str()))
		{
			_selectedTile.currentLayer = i;
		}
	}
	ImGui::Separator();
	
	if (ImGui::Button("Fill"))
	{
		if (_selectedTile._tileIndex >=0)
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
	ImGui::End();

	glm::vec2 mousePos = Input::GetMousePos();
	//ImGui::GetMou



}
