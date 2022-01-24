#include <GLFW/glfw3.h>
#include <gl/glew.h>
#include <nlohmann/json.hpp>
#include "imgui.h"
#include "TileMap.h"
#include "ResourceManager.h"
#include "Input.h"

#include "Texture2D.h"
#include <string>
//#include "glm.hpp"

class TileMapEditor
{
public:
	struct SelectedTile
	{
		Texture2D currentTexture;
		Sprite sprite;
		unsigned int currentLayer = 0;
		unsigned int _tileIndex = -1; //-1 if no tile is present upon click
	};

	void EnableEditor();
	void DisplayEditorGUI(GLFWwindow* window);

private:
	
	bool _isActive;

	//This bool represents if the tile data has been recieved from the relating tile map. If it has not, the data should be aqquired. 
	bool _hasTileData;
	std::string _mapName;
	std::string _textureName;
	glm::vec2 _mapSize;
	glm::vec2 _tileSize;

	SelectedTile _selectedTile;

	void AcquireData();
	void CreateTileMap(GLFWwindow* window);
	void SaveTileMap(const TileMap& map, const std::vector<bool>& collisionInfo);

};

