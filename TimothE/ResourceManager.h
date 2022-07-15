#pragma once
#include "pch.h"
#include "UID.h"


class Scene;
class Font;
class SpriteSheet;
class Texture2D;
class Shader;

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
	static Texture2D* GetTexture(std::string name);;
	static Shader* GetShader(std::string name);;
	static Scene* GetScene(std::string name);;
	static SpriteSheet* GetSpriteSheet(std::string name);
	static Font* GetFont(std::string name);;

private:
	static void LoadShaders();
	static void LoadFonts();
	static void LoadTextures();
	static void LoadSpritsheets();

private:
	static std::map<std::string, Texture2D*> _textures;
	static std::map<std::string, Shader*> _shaders;
	static std::map<std::string, Scene*> _scenes;
	static std::map<std::string, SpriteSheet*> _spritesheets;
	static std::map<std::string, Font*> _fonts;
};
