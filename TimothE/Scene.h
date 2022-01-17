#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "Renderer.h"

//  O.o
using namespace std;

class Scene
{
public:
	Scene(string name);
	~Scene();
	void Update(float deltaTime);
	void RenderScene(Renderer* pRenderer);
	GameObject* AddGameObject(GameObject* gameObject) { _listOfGameObjects.push_back(gameObject); return gameObject; }
	void RemoveGameObject(GameObject* gameObject);
	vector<GameObject*> GetGameObjects() { return _listOfGameObjects; }

	void LoadScene(const std::string& filename);
	void SaveScene(const std::string& filename);

private:
	string _name;
	int _id;
	static int nextID;
	vector<GameObject*> _listOfGameObjects;
};
