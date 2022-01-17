#pragma once
#include <GL/glew.h>
#include <map>
#include <string>
#include "UID.h"

class Shader;
class Texture2D;
class Scene;

static class ResourceManager
{
public:
	//instantiate functions
	void InstantiateTexture(std::string name, Texture2D* texture) { _textures[name] = texture; };
	void InstantiateShader(std::string name, Shader* shader) { _shaders[name] = shader; };
	void InstantiateScene(std::string name, Scene* scene) { _scenes[name] = scene; };

	//get functions
	Texture2D* GetTexture(std::string name) { return _textures[name]; };
	Shader* GetShader(std::string name) { return _shaders[name]; };
	Scene* GetScene(std::string name) { return _scenes[name]; };

	std::string GetUID() { return _UID; }

	//cleanup
	void Clear()
	{
		//// delete shaders	
		//for (auto& shader : _shaders)
		//	glDeleteProgram(shader.second.GetProgramID());
		//// delete textures
		//for (auto texture : _textures)
		//	glDeleteTextures(1, &texture.second.ID);
		//// delete scenes
		//for (auto scene : _scenes)
		//	glDeleteTextures(1, &scene.second.ID);
	};
private:
	static std::map<std::string, Texture2D*> _textures;
	static std::map<std::string, Shader*> _shaders;
	static std::map<std::string, Scene*> _scenes;

	std::string _UID = UID::GenerateUID();
};
