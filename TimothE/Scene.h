#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Camera.h"
#include "Window.h"

class Scene
{
public:
	Scene(std::string name);
	~Scene();
	
	//Triggers the gameobjects start methods
	void SceneStart();

	//Triggers the gameobjects end methods
	void SceneEnd();

	//Handles pausing the scene
	void ScenePause();

	//Any updates that need to be performed in the editor. Primarily every game objects transform
	void EditorUpdate(float deltaTime);

	void Update(float deltaTime);
	void RenderScene(Camera* cam);
	
	static void CircleBoxTest();

	GameObject* AddGameObject(GameObject* gameObject) { _listOfGameObjects.push_back(gameObject); return gameObject; }
	void RemoveGameObject(GameObject* gameObject);

	static void AddedComponentHandler(GameObject* gameObject, Component* comp);
	static void RemoveComponentHandler(GameObject* gameObject, Component* comp);

	std::vector<GameObject*> GetGameObjects() { return _listOfGameObjects; }

	void LoadScene(const std::string& filename);
	void SaveScene(const std::string& filename);

	//GameObject getters
	static GameObject* GetGameObjectByName(std::string name);
	static GameObject* GetGameObjectByID(std::string id);
	static GameObject* GetGameObjectByType(ObjectType type);
	static std::vector<GameObject*> GetGameObjectsByName(std::string name);
	static std::vector<GameObject*> GetGameObjectsByType(ObjectType type);

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

private:
	//Stores the name of the scene
	std::string _name;

	//Stores an id for the scene
	int _id;

	//Stores the next id for the scene
	static int nextID;

	//Stores a vector of game objects. This is refreshed every time a scene loads.
	static std::vector<GameObject*> _listOfGameObjects;
	static std::vector<GameObject*> _listOfDrawableGameObjects;

	GameObject* _pCircleTest;
	GameObject* _pTestObject2;
	GameObject* _pPlayer;
};
