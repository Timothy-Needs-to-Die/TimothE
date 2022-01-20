#include "ResourceManager.h"

std::map<std::string, Texture2D*> ResourceManager::_textures;
std::map<std::string, Shader*> ResourceManager::_shaders;
std::map<std::string, Scene*> ResourceManager::_scenes;

std::string ResourceManager::_UID;