#pragma once
#include <GL/glew.h>
#include <map>
#include "UID.h"

#include "Scene.h"
#include "Shader.h"
#include "Texture2D.h"

static class ResourceManager
{
public:
	static void Init() { _UID = UID::GenerateUID(); };

	//instantiate functions
	static void InstantiateTexture(std::string name, Texture2D* texture) { _textures.insert(pair<std::string, Texture2D*>(name, texture)); };
	static void InstantiateShader(std::string name, Shader* shader) { _shaders.insert(pair<std::string, Shader*>(name, shader)); };
	static void InstantiateScene(std::string name, Scene* scene) { _scenes.insert(pair<std::string, Scene*>(name, scene)); };

	//get functions
	static Texture2D* GetTexture(std::string name) { return _textures[name]; };
	static Shader* GetShader(std::string name) { return _shaders[name]; };
	static Scene* GetScene(std::string name) { return _scenes[name]; };

	static std::string GetUID() { return _UID; }
private:
	static std::map<std::string, Texture2D*> _textures;
	static std::map<std::string, Shader*> _shaders;
	static std::map<std::string, Scene*> _scenes;
	
	static std::string _UID;
};
