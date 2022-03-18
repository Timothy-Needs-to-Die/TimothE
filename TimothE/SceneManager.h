#pragma once
#include "pch.h"
#include "Scene.h"


class SceneManager
{
public:
	//Creates a new scene object with the specified name and returns the scene object
	static Scene* CreateScene(std::string name);

	//Gets a scene with the specified name
	static Scene* GetScene(std::string name);

	//Gets the current scene
	static Scene* GetCurrentScene();

	//Gets the default scene
	static Scene* GetDefaultScene();

	//Deletes a scene
	static void DeleteScene(std::string name);

	//Sets the default scene to the scene with the specified name
	static void SetDefaultScene(std::string name);

	//Sets the default scene to the passed in one
	static void SetDefaultScene(Scene* scene);

private:
	//Holds all of the scenes that the engine knows about
	static std::unordered_map<std::string, Scene*> _scenes;

	//Holds the default scene for the project
	static Scene* _pDefaultScene;

	static Scene* _pCurrentScene;

};

