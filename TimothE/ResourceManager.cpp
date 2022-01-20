#include "ResourceManager.h"

std::map<string, Texture2D*> ResourceManager::_textures;
std::map<string, Shader*> ResourceManager::_shaders;
std::map<string, Scene*> ResourceManager::_scenes;

std::string ResourceManager::_UID;

void ResourceManager::InstantiateTexture(string name, string path)
{ 
	Texture2D* texture = new Texture2D(path);
	_textures[name] = texture; 
};

void ResourceManager::InstantiateShader(string name, const char* vs, const char* fs)
{ 
	Shader* shader = new Shader(vs, fs);
	_shaders[name] = shader; 
};

void ResourceManager::InstantiateScene(string name, Scene* scene)
{ 
	_scenes[name] = scene; 
};