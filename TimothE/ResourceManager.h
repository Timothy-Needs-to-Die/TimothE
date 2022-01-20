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
	static void InstantiateTexture(string name, string path);
	static void InstantiateShader(string name, const char* vs, const char* fs);
	static void InstantiateScene(string name, Scene* scene);

	//get functions
	static Texture2D* GetTexture(string name) { return _textures[name]; };
	static Shader* GetShader(string name) { return _shaders[name]; };
	static Scene* GetScene(string name) { return _scenes[name]; };

	static std::string GetUID() { return _UID; }
private:
	static std::map<string, Texture2D*> _textures;
	static std::map<string, Shader*> _shaders;
	static std::map<string, Scene*> _scenes;
	
	static string _UID;
};
