#pragma once
#include <GLFW/glfw3.h>
#include <list>
#include <string>
#include "GameObject.h"
#include "Graphics.h"


using namespace std;

class Scene
{
public:
	Scene(string name);
	~Scene();
	void Update(float deltaTime);
	void RenderScene(GLFWwindow* pWindow, Graphics* pGraphics);
	void AddGameObject(GameObject* gameObject) { _listOfGameObjects.push_back(gameObject); }
	void RemoveGameObject(GameObject* gameObject) { _listOfGameObjects.remove(gameObject); }

private:
	string _name;
	int _id;
	static int nextID;
	list<GameObject*> _listOfGameObjects;
};
