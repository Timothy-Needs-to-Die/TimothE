#include "ResourceManager.h"

std::map<std::string, Texture2D*> ResourceManager::_textures;
std::map<std::string, Shader*> ResourceManager::_shaders;
std::map<std::string, Scene*> ResourceManager::_scenes;

std::string ResourceManager::_UID;

void ResourceManager::Init()
{
	_UID = UID::GenerateUID();

	//LOAD TEXTURES
	ResourceManager::InstantiateTexture("lenna", new Texture2D("lenna3.jpg"));

	//LOAD SHADERS
	ResourceManager::InstantiateShader("ui", new Shader("vr_UIShader.vert", "fr_UIShader.frag"));
	ResourceManager::InstantiateShader("default", new Shader("VertexShader.vert", "FragmentShader.frag"));

	//LOAD SCENES

	//LOAD SOUNDS
	
	//LOAD FONTS
}

void ResourceManager::Shutdown()
{
	for (auto& tex : _textures)
	{
		unsigned int id = tex.second->GetID();
		glDeleteTextures(1, &id);
	}

	_textures.clear();
	_shaders.clear();
	_scenes.clear();
}

void ResourceManager::InstantiateTexture(std::string name, Texture2D* texture)
{ 
	_textures[name] = texture;
};

void ResourceManager::InstantiateShader(std::string name, Shader* shader)
{ 
	_shaders[name] = shader;
};

void ResourceManager::InstantiateScene(std::string name, Scene* scene)
{ 
	_scenes[name] = scene; 
}

//void ResourceManager::InstantiateSound(std::string name, SoundStruct* sound)
//{
//	_sounds[name] = sound;
//}