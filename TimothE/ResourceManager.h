#pragma once
#include "pch.h"
#include "UID.h"

#include "Core/Graphics/Shader.h"
#include "Texture2D.h"
#include "SpriteSheet.h"
#include "Font.h"

class Scene;

//#include "AudioEngine.h"

static class ResourceManager
{
public:
	static void Init();
	static void Shutdown();

	//instantiate object functions
	static void InstantiateTexture(std::string name, Texture2D* texture);
	static void InstantiateShader(std::string name, Shader* shader);
	static void InstantiateScene(std::string name, Scene* scene);
	static void InstantiateSpritesheet(std::string name, SpriteSheet* spritesheet);
	static void InstantiateFont(std::string name, Font* sound);

	//get functions
	static Texture2D* GetTexture(std::string name) { return _textures[name]; };
	static Shader* GetShader(std::string name) { return _shaders[name]; };
	static Scene* GetScene(std::string name) { return _scenes[name]; };
	static SpriteSheet* GetSpriteSheet(std::string name) { return _spritesheets[name]; }
	static Font* GetFont(std::string name) { return _fonts[name]; };

	static std::string GetUID() { return _UID; }

private:
	static void LoadFonts();

private:
	static std::map<std::string, Texture2D*> _textures;
	static std::map<std::string, Shader*> _shaders;
	static std::map<std::string, Scene*> _scenes;
	static std::map<std::string, SpriteSheet*> _spritesheets;
	static std::map<std::string, Font*> _fonts;
	
	static std::string _UID;
};
