#pragma once
#include <GL/glew.h>
#include <map>
#include <string>
#include "Scene.h"
#include "UID.h"
#include "Shader.h"
#include "Texture2D.h"

class Shader;
class Texture2D;

static class ResourceManager
{
public:
	//instantiate functions
	void InstantiateTexture(std::string name, Texture2D* texture) { _textures[name] = texture; };
	void InstantiateShader(std::string name, Shader* shader) { _shaders[name] = shader; };
	void InstantiateScene(std::string name, Scene* scene) { _scenes[name] = scene; };

	//get functions
	static Texture2D* GetTexture(std::string name) { return _textures[name]; };
	Shader* GetShader(std::string name) { return _shaders[name]; };
	Scene* GetScene(std::string name) { return _scenes[name]; };

	std::string GetUID() { return _UID; }
private:
	static std::map<std::string, Texture2D*> _textures;
	static std::map<std::string, Shader*> _shaders;
	static std::map<std::string, Scene*> _scenes;
	
	std::string _UID = UID::GenerateUID();
};
