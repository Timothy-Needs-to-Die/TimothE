#include "pch.h"
#include "SceneManager.h"


void SceneManager::Init()
{

}

Scene* SceneManager::CreateScene(Scene* scene)
{
	_scenes[scene->GetName()] = scene;

	return scene;
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
	_pDefaultScene->InitScene();

	return _pDefaultScene;
}

Scene* SceneManager::SetCurrentScene(Scene* scene, glm::vec2 spawnPoint)
{
	if (_pCurrentScene != nullptr) {
		_pCurrentScene->Unload();
	}

	if (scene != nullptr) {
		_pCurrentScene = scene;
		_pCurrentScene->InitScene();
		_pCurrentScene->SceneStart(spawnPoint);

		//_pCurrentScene->LoadScene("Resources/Scenes/" + scene->GetName() + ".scene");
	}

	return _pCurrentScene;
}

Scene* SceneManager::SetCurrentScene(std::string name, glm::vec2 spawnPoint)
{
	Scene* scene = _scenes[name];
	if (scene != nullptr) {
		return SetCurrentScene(scene, spawnPoint);
	}
	else {
		std::cout << "Scene Not found: " << name << std::endl;
	}

	return nullptr;
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

void SceneManager::LoadAllTilemaps()
{
	for (auto& scene : _scenes) {
		scene.second->LoadTileMap();
	}
}

std::unordered_map<std::string, Scene*> SceneManager::_scenes;
Scene* SceneManager::_pDefaultScene;
Scene* SceneManager::_pCurrentScene;
