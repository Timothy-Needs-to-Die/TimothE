#include "SceneManager.h"

//TODO: Add error statments and such to this class
//TODO: Document this file

void SceneManager::Init()
{
	//TODO: Load list of scenes from file and load the default one
	//TODO: Add all the scenes found to the list of files.
	//TODO: Neaten content browser a fuck tonne.
	_pDefaultScene = new Scene();
	_pCurrentScene = _pDefaultScene;

	std::vector<string> sceneFiles = Editor::GetDirectoriesOfType(".scene", "Resources/Scenes/");

	for (auto& s : sceneFiles) {
		std::cout << s << std::endl;

		int extensionLocation = s.find(".scene");
		if (extensionLocation != std::string::npos) {
			std::string rString = s.erase(extensionLocation);

			int lastSlashLocation = rString.find_last_of("/");
			if (lastSlashLocation != std::string::npos) {
				rString = rString.substr(lastSlashLocation);
			}

			//std::cout << rString << std::endl;

			Scene* scene = new Scene(rString);
			_scenes.emplace(rString, scene);
		}

	}
}

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
	_pDefaultScene->InitScene();

	return _pDefaultScene;
}

Scene* SceneManager::SetCurrentScene(Scene* scene)
{
	if (scene != nullptr) {
		_pCurrentScene->Unload();
		_pCurrentScene = scene;
		_pCurrentScene->LoadScene("Resources/Scenes/" + scene->GetName() + ".scene");
	}

	return _pCurrentScene;
}

Scene* SceneManager::SetCurrentScene(std::string name)
{
	Scene* scene = _scenes[name];
	if (scene != nullptr) {
		return SetCurrentScene(scene);
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

std::unordered_map<std::string, Scene*> SceneManager::_scenes;
Scene* SceneManager::_pDefaultScene;
Scene* SceneManager::_pCurrentScene;
