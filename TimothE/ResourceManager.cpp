#include "ResourceManager.h"

std::map<string, Texture2D*> ResourceManager::_textures;
std::map<string, Shader*> ResourceManager::_shaders;
std::map<string, Scene*> ResourceManager::_scenes;

std::string ResourceManager::_UID;

void ResourceManager::InstantiateTexture(string name, string path)
{ 
	_textures[name] = new Texture2D(path);
};

void ResourceManager::InstantiateShader(string name, const char* vs, const char* fs)
{ 
	_shaders[name] = new Shader(vs, fs);
};

void ResourceManager::InstantiateScene(string name, Scene* scene)
{ 
	_scenes[name] = scene; 
};