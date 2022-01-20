#pragma once

#include <vector>
#include <string>
#include <glm.hpp>
#include <fstream>
#include "Component.h"
#include "GameObject.h"


//Tilemap Structs

struct TileTextureData {
	std::string name;
	std::string filePath;
	glm::vec3 tint;
};

struct TileMapTexture {
	TileTextureData data;
	int tileValue;
};

struct TileMap {
	std::string filePath;
	std::vector<TileMapTexture> textures;
	std::vector<std::vector<unsigned int>> tileValue;
};


//The tilemap will be a gameObject with an x and y size
//There must also be a variable for tile size
//A tilemap must have the option to be exported to a file (possibly txt?)
//Buildings may have to be considered into this system in the future, however they may be on a different tileMap

//The tile map component should be capable of building tilemaps in the editor and saving them to an external file to be re-used.
//It should also be able to load in tile maps from files (txt)

class TileMapComponent : public Component
{
public:
	COMPONENT_STATIC_TYPE(TileMap_Type);
	TileMapComponent();


	~TileMapComponent();
	glm::vec2 mapSize;
	glm::vec2 tileSize;
	//Bool to show the value stored in the current grid
	bool showValues;



	void LoadTileMap(TileMap tileMap);
	void SaveTileMap(TileMap tileMap);
	int ChangeTileValue(int value, TileMapTexture);

	// ============= Component Stuff ============= // 
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	GameObject* _parent;
	void SetGameObject(GameObject* newParent) {
		_parent = newParent;
	}
		// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		return true;
	}
	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		return true;
	}
	// Inherited via Component
	virtual void DrawEditorUI() override;
	// =========================================== //


private:
	TileMap _currentEditorTileMap;
};

