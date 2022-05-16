#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Camera.h"
#include "Core/Graphics/Window.h"
#include "TileMap.h"
#include "Physics.h"
#include "AnimatedSpritesheet.h"
#include "Tag.h"
#include <vector>
#include "Day.h"

//TODO: Document and order this class

class Scene
{
public:
	Scene() {

		_name = "DefaultScene";
		_pTilemap = new TileMap("DefaultScene");
		//Save();
		InitScene();
	}

	Scene(std::string name);
	~Scene();

	//Triggers the gameobjects start methods
	void SceneStart();

	virtual void InitScene();

	//Triggers the gameobjects end methods
	void SceneEnd();

	//Handles pausing the scene
	void ScenePause();

	//Any updates that need to be performed in the editor. Primarily every game objects transform
	void EditorUpdate();

	TileMap* GetTileMap() { return _pTilemap; }

	void Update();
	virtual void UpdateUI();
	virtual void UpdateObjects();



	void RenderScene(Camera* cam);

	//TODO: Implement unloading logic.
	void Unload() {
		for (auto& obj : _listOfGameObjects) {
			delete obj;
			obj = nullptr;
		}
		_listOfGameObjects.clear();
		_listOfDrawableGameObjects.clear();

		delete _pTilemap;
		_pTilemap = nullptr;
	}

	static void CircleBoxTest();
	static void SceneBox();

	std::string GetName() const { return _name; }

	GameObject* AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* gameObject);

	static void AddedComponentHandler(GameObject* gameObject, Component* comp);
	static void RemoveComponentHandler(GameObject* gameObject, Component* comp);

	std::vector<GameObject*> GetGameObjects() { return _listOfGameObjects; }

	//void LoadScene(const std::string& filename);
	//void SaveScene(const std::string& filename);
	/*void Save();*/

	//GameObject getters
	static GameObject* GetGameObjectByName(std::string name);
	static GameObject* GetGameObjectByID(std::string id);



	static std::vector<GameObject*> GetGameObjectsByName(std::string name);


	glm::vec2 ConvertWorldToScreen(glm::vec2 inPos) {
		glm::vec2 outPos{ inPos.x / Window::GetWidth(), inPos.y / Window::GetHeight() };
		return outPos;
	}

	/////////////
	//DO NOT MOVE
	/////////////
	//Template methods. Have to be in the header in order for them to work. 

	//Gets a pointer to the component of type T
	template<typename T>
	static T* FindObjectOfType() {
		for (GameObject* obj : _listOfGameObjects) {
			T* comp = obj->GetComponent<T>();
			if (comp != nullptr)
			{
				return comp;
			}
		}
		return nullptr;
	}

	//Gets a vector of the passed in component type (T).
	template<typename T>
	static std::vector<T*> FindObjectsOfType() {
		std::vector<T*> compList;
		for (GameObject* obj : _listOfGameObjects) {
			T* comp = obj->GetComponent<T>();
			if (comp != nullptr)
			{
				compList.emplace_back(comp);
			}
		}
		return compList;
	}

	// Tag Handling // 
	GameObject* FindObjectWithTag(const std::string& tagName);
	std::vector<GameObject*> FindGameObjectsWithTag(const std::string& tagName);


protected:
	//Stores the name of the scene
	std::string _name;
	TileMap* _pTilemap;

private:
	//Stores an id for the scene
	int _id;

	//Stores the next id for the scene
	static int nextID;

	//Stores a vector of game objects. This is refreshed every time a scene loads.
	static std::vector<GameObject*> _listOfGameObjects;
	static std::vector<GameObject*> _listOfDrawableGameObjects;
	std::vector<GameObject*> _gameObjectsToRemove;

	bool _isInitialized = false;

	Day* _pDay;
	bool _timeProgression = true;
};
