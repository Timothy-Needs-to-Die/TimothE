#pragma once
#include "pch.h"
#include "Scene.h"
#include "Editor.h"

class SceneManager
{
public:
	static void Init();

	static Scene* CreateScene(Scene* scene);

	//Gets a scene with the specified name
	static Scene* GetScene(std::string name);

	//Gets the current scene
	static Scene* GetCurrentScene();

	//Gets the default scene
	static Scene* GetDefaultScene();

	//Sets the current scene to the passed in one
	static Scene* SetCurrentScene(Scene* scene);

	//Sets the current scene to the passed in one by the name
	static Scene* SetCurrentScene(std::string name);

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

