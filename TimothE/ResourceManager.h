#pragma once
#include "pch.h"
#include "UID.h"

#include "Shader.h"
#include "Texture2D.h"
//#include "AudioEngine.h"
class Scene;

static class ResourceManager
{
public:
	static void Init();

	//instantiate object functions
	static void InstantiateTexture(std::string name, Texture2D* texture);
	static void InstantiateShader(std::string name, Shader* shader);
	static void InstantiateScene(std::string name, Scene* scene);
	//static void InstantiateSound(std::string name, SoundStruct* sound);

	//get functions
	static Texture2D* GetTexture(std::string name) { return _textures[name]; };
	static Shader* GetShader(std::string name) { return _shaders[name]; };
	static Scene* GetScene(std::string name) { return _scenes[name]; };
	//static SoundStruct* GetSound(std::string name) { return _sounds[name]; };

	static std::string GetUID() { return _UID; }
private:
	static std::map<std::string, Texture2D*> _textures;
	static std::map<std::string, Shader*> _shaders;
	static std::map<std::string, Scene*> _scenes;
	//std::map<std::string, SoundStruct*> _sounds;
	
	static std::string _UID;
};
