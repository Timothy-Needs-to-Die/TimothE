#include "pch.h"
#include "ResourceManager.h"
#include "Core/Graphics/OpenGLError.h"
#include "FarmScene.h"
#include "MainMenuScene.h"
#include "Dirent.h"
#include "misc/cpp/imgui_stdlib.h"

#include "FarmScene.h"
#include "TownScene.h"
#include "EastPlainsScene.h"

#include "Core/Graphics/Shader.h"
#include "Texture2D.h"
#include "SpriteSheet.h"
#include "Font.h"


std::map<std::string, Texture2D*> ResourceManager::_textures;
std::map<std::string, Shader*> ResourceManager::_shaders;
std::map<std::string, Scene*> ResourceManager::_scenes;
std::map<std::string, SpriteSheet*> ResourceManager::_spritesheets;
std::map<std::string, Font*> ResourceManager::_fonts;

void ResourceManager::Init()
{
	//LOAD SCENES
	ResourceManager::InstantiateScene("MainMenuScene", new MainMenuScene("MainMenuScene"));
	ResourceManager::InstantiateScene("FarmScene", new FarmScene("FarmScene"));
	ResourceManager::InstantiateScene("TownScene", new TownScene("TownScene"));
	ResourceManager::InstantiateScene("EastPlains", new EastPlainsScene("EastPlains"));

	LoadTextures();
	LoadSpritsheets();
	LoadShaders();
	LoadFonts();


	//LOAD SOUNDS
}

void ResourceManager::Shutdown()
{
	for (auto& tex : _textures)
	{
		unsigned int id = tex.second->GetID();
		GLCall(glDeleteTextures(1, &id));
	}

	_textures.clear();
	_shaders.clear();
	_scenes.clear();
}


void ResourceManager::LoadShaders()
{
	ResourceManager::InstantiateShader("ui", new Shader("Resources/Shaders/vr_UIShader.vert", "Resources/Shaders/fr_UIShader.frag"));
	ResourceManager::InstantiateShader("default", new Shader("Resources/Shaders/VertexShader.vert", "Resources/Shaders/FragmentShader.frag"));
	ResourceManager::InstantiateShader("framebuffer", new Shader("Resources/Shaders/Breakout.vert", "Resources/Shaders/Breakout.frag"));
}

void ResourceManager::LoadFonts()
{
	std::ofstream fileStream("./Resources/Fonts");
	_fonts.clear();
	DIR* directory = opendir("./Resources/Fonts");
	struct dirent* dirent;
	if (directory)
	{
		while ((dirent = readdir(directory)) != NULL)
		{
			if (dirent->d_type == 32768)
			{
				std::string fn = "Resources/Fonts/" + std::string(dirent->d_name);
				InstantiateFont(dirent->d_name, new Font(fn));

				std::cout << "Font loaded: " << dirent->d_name << std::endl;
			}
		}
		closedir(directory);
	}
}


void ResourceManager::LoadTextures()
{
	std::ofstream fileStream("./Resources/Images");
	_fonts.clear();
	DIR* directory = opendir("./Resources/Images");
	struct dirent* dirent;
	if (directory)
	{
		while ((dirent = readdir(directory)) != NULL)
		{
			if (dirent->d_type == 32768)
			{
				std::string filename = std::string(dirent->d_name);
				std::string extension = filename.substr(filename.length() - 4);

				if (extension == ".pdn") continue;

				std::string fn = "Resources/Images/" + filename;

				if (fn == "Resources/Images/PlayerSheet_Updated.png") {
					InstantiateTexture(dirent->d_name, new Texture2D(fn, true));
				}
				else {
					InstantiateTexture(dirent->d_name, new Texture2D(fn));
				}


				std::cout << "Image loaded: " << dirent->d_name << std::endl;
			}
		}
		closedir(directory);
	}

	directory = opendir("Resources/Images/Spritesheets");
	if (directory) {
		while ((dirent = readdir(directory)) != NULL)
		{
			if (dirent->d_type == 32768)
			{
				std::string filename = std::string(dirent->d_name);
				std::string extension = filename.substr(filename.length() - 4);

				if (extension == ".pdn") continue;

				std::string fn = "Resources/Images/Spritesheets/" + filename;
				InstantiateTexture(dirent->d_name, new Texture2D(fn));

				std::cout << "Image loaded: " << dirent->d_name << std::endl;
			}
		}
		closedir(directory);
	}
}


void ResourceManager::LoadSpritsheets()
{
	ResourceManager::InstantiateSpritesheet("Overworld_Spring", new SpriteSheet(ResourceManager::GetTexture("Overworld_Spring.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("itemspritesheet", new SpriteSheet(ResourceManager::GetTexture("ItemsSheet.png"), 128, 128));
	ResourceManager::InstantiateSpritesheet("cropspritesheet", new SpriteSheet(ResourceManager::GetTexture("CropsSheet.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("dungeonGrey", new SpriteSheet(ResourceManager::GetTexture("DungeonGreySprites.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("TMX Tester", new SpriteSheet(ResourceManager::GetTexture("TMX Tester.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("swords", new SpriteSheet(ResourceManager::GetTexture("swords.png"), 16, 16));
	ResourceManager::InstantiateSpritesheet("axes", new SpriteSheet(ResourceManager::GetTexture("axes.png"), 16, 16));
	ResourceManager::InstantiateSpritesheet("pickaxes", new SpriteSheet(ResourceManager::GetTexture("pickaxes.png"), 16, 16));
	ResourceManager::InstantiateSpritesheet("planks", new SpriteSheet(ResourceManager::GetTexture("Planks.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("wall", new SpriteSheet(ResourceManager::GetTexture("Wall.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("fireball", new SpriteSheet(ResourceManager::GetTexture("Fireball.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("small_stone", new SpriteSheet(ResourceManager::GetTexture("Rock.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("small_wood", new SpriteSheet(ResourceManager::GetTexture("TreeStump.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("small_metal", new SpriteSheet(ResourceManager::GetTexture("Metal.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("small_coal", new SpriteSheet(ResourceManager::GetTexture("Coal.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("campfire", new SpriteSheet(ResourceManager::GetTexture("Campfire.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("bed", new SpriteSheet(ResourceManager::GetTexture("Bed.png"), 32, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("testSheet", new SpriteSheet(ResourceManager::GetTexture("testSheet.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	ResourceManager::InstantiateSpritesheet("player", new SpriteSheet(ResourceManager::GetTexture("PlayerSheet_Updated.png"), 16, 32));
	ResourceManager::InstantiateSpritesheet("swords_new", new SpriteSheet(ResourceManager::GetTexture("Swords_New.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
	
	
	ResourceManager::InstantiateSpritesheet("roguespritesheet", new SpriteSheet(ResourceManager::GetTexture("RogueSprites.png"), 17, 17));
	ResourceManager::InstantiateSpritesheet("extraspritesheet", new SpriteSheet(ResourceManager::GetTexture("ExtraSpriteSheet.png"), 15, 15));
	ResourceManager::InstantiateSpritesheet("RPGpack_sheet", new SpriteSheet(ResourceManager::GetTexture("RPGpack_sheet.png"), 64, 64));
	ResourceManager::InstantiateSpritesheet("tower", new SpriteSheet(ResourceManager::GetTexture("Tower.png"), 213, 254));
	ResourceManager::InstantiateSpritesheet("medispritesheet", new SpriteSheet(ResourceManager::GetTexture("MediSprites.png"), TILE_SIZE_IN_PIXELS, TILE_SIZE_IN_PIXELS));
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

void ResourceManager::InstantiateSpritesheet(std::string name, SpriteSheet* spritesheet)
{
	spritesheet->SetResourceName(name);
	_spritesheets[name] = spritesheet;
}

void ResourceManager::InstantiateFont(std::string name, Font* font)
{
	_fonts[name] = font;
}

Texture2D* ResourceManager::GetTexture(std::string name)
{
	try {
		Texture2D* pTexture = _textures.at(name);
		if (pTexture != nullptr) {
			return pTexture;
		}
	}
	catch (std::out_of_range & e) {
		TIM_LOG_ERROR("Texture: " << name << " could not be found in resource manager");
		__debugbreak();
	}

	return _textures.at("whiteTexture");
}

Shader* ResourceManager::GetShader(std::string name)
{
	try {
		Shader* pShader = _shaders.at(name);
		if (pShader != nullptr) {
			return pShader;
		}
	}
	catch (std::out_of_range & e) {
		TIM_LOG_ERROR("Shader: " << name << " could not be found in resource managaer");
		__debugbreak();
	}


	return nullptr;
}

Scene* ResourceManager::GetScene(std::string name)
{
	try {
		Scene* pScene = _scenes.at(name);

		if (pScene != nullptr) {
			return pScene;
		}
	}
	catch (std::out_of_range & e) {
		TIM_LOG_ERROR("Scene: " << name << " could not be found in resource manager");
		__debugbreak();
	}

	return nullptr;
}

SpriteSheet* ResourceManager::GetSpriteSheet(std::string name)
{
	try {
		SpriteSheet* pSpritesheet = _spritesheets.at(name);

		if (pSpritesheet != nullptr) {
			return pSpritesheet;
		}
	}
	catch (std::out_of_range & e) {
		TIM_LOG_ERROR("Spritesheet: " << name << " could not be found in resource manager");
		__debugbreak();
	}

	return nullptr;
}

Font* ResourceManager::GetFont(std::string name)
{
	try {
		Font* pFont = _fonts.at(name);

		if (pFont != nullptr) {
			return pFont;
		}
	}
	catch (std::out_of_range & e) {
		TIM_LOG_ERROR("Font: " << name << " could not be found in resource manager");
		__debugbreak();
	}

	return nullptr;
}
