#include "SceneManager.h"

Scene* SceneManager::CreateScene(std::string name)
{
	Scene* newScene = new Scene(name);

	_scenes[name] = newScene;
	
	return newScene;
}

Scene* SceneManager::GetScene(std::string name)
{
	return _scenes[name];
}

Scene* SceneManager::GetCurrentScene()
{
	if (_pCurrentScene == nullptr) {
		_pCurrentScene = GetDefaultScene();
	}

	return _pCurrentScene;
}

Scene* SceneManager::GetDefaultScene()
{
	if (_pDefaultScene == nullptr) {
		//TODO: Create a blank scene template
	}

	return _pDefaultScene;
}

void SceneManager::DeleteScene(std::string name)
{
	if (_scenes[name] != nullptr) {
		_scenes.erase(name);
	}
}

void SceneManager::SetDefaultScene(std::string name)
{
	Scene* scene = GetScene(name);

	if (scene != nullptr) {
		_pDefaultScene = scene;
	}

}

void SceneManager::SetDefaultScene(Scene* scene)
{
	_pDefaultScene = scene;
}

std::unordered_map<std::string, Scene*> SceneManager::_scenes;
Scene* SceneManager::_pDefaultScene;
Scene* SceneManager::_pCurrentScene;
