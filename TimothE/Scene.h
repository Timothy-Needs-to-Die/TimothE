#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "Renderer.h"

class Scene
{
public:
	Scene(string name);
	~Scene();
	
	void SceneStart();
	void SceneEnd();
	void ScenePause();
	void EditorUpdate();

	void Update(float deltaTime);
	void RenderScene(Renderer* pRenderer, Camera* cam);
	GameObject* AddGameObject(GameObject* gameObject) { _listOfGameObjects.push_back(gameObject); return gameObject; }
	void RemoveGameObject(GameObject* gameObject);
	vector<GameObject*> GetGameObjects() { return _listOfGameObjects; }

	void LoadScene(const std::string& filename);
	void SaveScene(const std::string& filename);


	static GameObject* GetGameObjectByName(std::string name);
	static GameObject* GetGameObjectByID(std::string id);
	static GameObject* GetGameObjectByType(ObjectType type);
	static std::vector<GameObject*> GetGameObjectsByName(std::string name);
	static std::vector<GameObject*> GetGameObjectsByType(ObjectType type);

private:
	string _name;
	int _id;
	static int nextID;
	static std::vector<GameObject*> _listOfGameObjects;
};
