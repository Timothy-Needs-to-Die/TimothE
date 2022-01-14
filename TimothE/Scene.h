#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "Renderer.h"


using namespace std;

class Scene
{
public:
	Scene(string name);
	~Scene();
	void Update(float deltaTime);
	void RenderScene(Renderer* pRenderer);
	void AddGameObject(GameObject* gameObject) { _listOfGameObjects.push_back(gameObject); }
	void RemoveGameObject(GameObject* gameObject);
	vector<GameObject*> GetGameObjects() { return _listOfGameObjects; }

private:
	string _name;
	int _id;
	static int nextID;
	vector<GameObject*> _listOfGameObjects;
};
