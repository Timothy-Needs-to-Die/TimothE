#include "pch.h"
#include "ResourceManager.h"
#include "Core/Graphics/OpenGLError.h"
#include "FarmScene.h"
#include "MainMenuScene.h"
#include "Dirent.h"
#include "misc/cpp/imgui_stdlib.h"

#include "FarmScene.h"
#include "TownScene.h"

std::map<std::string, Texture2D*> ResourceManager::_textures;
std::map<std::string, Shader*> ResourceManager::_shaders;
std::map<std::string, Scene*> ResourceManager::_scenes;
std::map<std::string, SpriteSheet*> ResourceManager::_spritesheets;
std::map<std::string, Font*> ResourceManager::_fonts;

void ResourceManager::Init()
{
	//LOAD TEXTURES
	ResourceManager::InstantiateTexture("player", new Texture2D("Resources/Images/Spritesheets/PlayerSpritesheet.png", true));
	ResourceManager::InstantiateTexture("enemy", new Texture2D("Resources/Images/Spritesheets/EnemySpritesheet.png", true));
	ResourceManager::InstantiateTexture("bed", new Texture2D("Resources/Images/Bed.png", true));
	ResourceManager::InstantiateTexture("cropspritesheet", new Texture2D("Resources/Images/Spritesheets/CropsSheet.png", true));
	ResourceManager::InstantiateTexture("spritesheet", new Texture2D("Resources/Images/Spritesheets/RPGpack_sheet.png", false));
	ResourceManager::InstantiateTexture("medispritesheet", new Texture2D("Resources/Images/Spritesheets/MediSprites.png", true));
	ResourceManager::InstantiateTexture("roguespritesheet", new Texture2D("Resources/Images/Spritesheets/RogueSprites.png", true));
	ResourceManager::InstantiateTexture("itemspritesheet", new Texture2D("Resources/Images/Spritesheets/ItemsSheet.png", true));
	ResourceManager::InstantiateTexture("animalspritesheet", new Texture2D("Resources/Images/Spritesheets/AnimalSheet.png", true));
	ResourceManager::InstantiateTexture("extraspritesheet", new Texture2D("Resources/Images/Spritesheets/ExtraSpriteSheet.png", true));
	ResourceManager::InstantiateTexture("buildspritesheet", new Texture2D("Resources/Images/Spritesheets/BuildingSheet.png", true));
	ResourceManager::InstantiateTexture("build2spritesheet", new Texture2D("Resources/Images/Spritesheets/BuildingSheet2.png", true));
	ResourceManager::InstantiateTexture("Button", new Texture2D("Resources/Images/ButtonTest.png"));
	ResourceManager::InstantiateTexture("swords", new Texture2D("Resources/Images/swords.png", true));
	ResourceManager::InstantiateTexture("axes", new Texture2D("Resources/Images/axes.png"));
	ResourceManager::InstantiateTexture("pickaxes", new Texture2D("Resources/Images/pickaxes.png"));
	ResourceManager::InstantiateTexture("small_stone", new Texture2D("Resources/Images/Rock.png"));
	ResourceManager::InstantiateTexture("small_wood", new Texture2D("Resources/Images/TreeStump.png"));
	ResourceManager::InstantiateTexture("small_metal", new Texture2D("Resources/Images/Metal.png"));
	ResourceManager::InstantiateTexture("small_coal", new Texture2D("Resources/Images/Coal.png"));
	ResourceManager::InstantiateTexture("planks", new Texture2D("Resources/Images/Planks.png"));
	ResourceManager::InstantiateTexture("wall", new Texture2D("Resources/Images/Wall.png", true));
	ResourceManager::InstantiateTexture("tower", new Texture2D("Resources/Images/Tower.png", true));
	ResourceManager::InstantiateTexture("fireball", new Texture2D("Resources/Images/Fireball.png", true));
	ResourceManager::InstantiateTexture("whiteTexture", new Texture2D("Resources/Images/whiteTexture.png"));
	ResourceManager::InstantiateTexture("campfire", new Texture2D("Resources/Images/Campfire.png", true));
	ResourceManager::InstantiateTexture("gameover_bg", new Texture2D("Resources/Images/Game Over.png", true));
	ResourceManager::InstantiateTexture("testSheet", new Texture2D("Resources/Images/testSheet.png", true));
	


	//LOAD SPRITESHEETS
	ResourceManager::InstantiateSpritesheet("spritesheet", new SpriteSheet(ResourceManager::GetTexture("spritesheet"), 64, 64, "spritesheet"));
	ResourceManager::InstantiateSpritesheet("medispritesheet", new SpriteSheet(ResourceManager::GetTexture("medispritesheet"), 64, 64, "medispritesheet"));
	ResourceManager::InstantiateSpritesheet("itemspritesheet", new SpriteSheet(ResourceManager::GetTexture("itemspritesheet"), 128, 128, "itemspritesheet"));
	ResourceManager::InstantiateSpritesheet("cropspritesheet", new SpriteSheet(ResourceManager::GetTexture("cropspritesheet"), 32, 32, "cropspritesheet"));
	ResourceManager::InstantiateSpritesheet("roguespritesheet", new SpriteSheet(ResourceManager::GetTexture("roguespritesheet"), 17, 17, "roguespritesheet"));
	ResourceManager::InstantiateSpritesheet("animalspritesheet", new SpriteSheet(ResourceManager::GetTexture("animalspritesheet"), 32, 32, "animalspritesheet"));
	ResourceManager::InstantiateSpritesheet("extraspritesheet", new SpriteSheet(ResourceManager::GetTexture("extraspritesheet"), 15, 15, "extraspritesheet"));
	ResourceManager::InstantiateSpritesheet("buildspritesheet", new SpriteSheet(ResourceManager::GetTexture("buildspritesheet"), 32, 32, "buildspritesheet"));
	ResourceManager::InstantiateSpritesheet("build2spritesheet", new SpriteSheet(ResourceManager::GetTexture("build2spritesheet"), 32, 32, "buildspritesheet"));
	ResourceManager::InstantiateSpritesheet("swords", new SpriteSheet(ResourceManager::GetTexture("swords"), 16, 16, "swords"));
	ResourceManager::InstantiateSpritesheet("axes", new SpriteSheet(ResourceManager::GetTexture("axes"), 16, 16, "axes"));
	ResourceManager::InstantiateSpritesheet("pickaxes", new SpriteSheet(ResourceManager::GetTexture("pickaxes"), 16, 16, "pickaxes"));
	ResourceManager::InstantiateSpritesheet("planks", new SpriteSheet(ResourceManager::GetTexture("planks"), 64, 64, "pickaxes"));
	ResourceManager::InstantiateSpritesheet("wall", new SpriteSheet(ResourceManager::GetTexture("wall"), 64, 64, "wall"));
	ResourceManager::InstantiateSpritesheet("tower", new SpriteSheet(ResourceManager::GetTexture("tower"), 213, 254, "tower"));
	ResourceManager::InstantiateSpritesheet("fireball", new SpriteSheet(ResourceManager::GetTexture("fireball"), 64, 64, "fireball"));
	ResourceManager::InstantiateSpritesheet("small_stone", new SpriteSheet(ResourceManager::GetTexture("small_stone"), 32, 32, "small_stone"));
	ResourceManager::InstantiateSpritesheet("small_wood", new SpriteSheet(ResourceManager::GetTexture("small_wood"), 32, 32, "small_wood"));
	ResourceManager::InstantiateSpritesheet("small_metal", new SpriteSheet(ResourceManager::GetTexture("small_metal"), 32, 32, "small_metal"));
	ResourceManager::InstantiateSpritesheet("small_coal", new SpriteSheet(ResourceManager::GetTexture("small_coal"), 32, 32, "small_coal"));
	ResourceManager::InstantiateSpritesheet("campfire", new SpriteSheet(ResourceManager::GetTexture("campfire"), 32, 32, "campfire"));
	ResourceManager::InstantiateSpritesheet("bed", new SpriteSheet(ResourceManager::GetTexture("bed"), 32, 64, "bed"));
	ResourceManager::InstantiateSpritesheet("testSheet", new SpriteSheet(ResourceManager::GetTexture("testSheet"), 64, 64, "testSheet"));


	//LOAD SHADERS
	ResourceManager::InstantiateShader("ui", new Shader("Resources/Shaders/vr_UIShader.vert", "Resources/Shaders/fr_UIShader.frag"));
	ResourceManager::InstantiateShader("default", new Shader("Resources/Shaders/VertexShader.vert", "Resources/Shaders/FragmentShader.frag"));

	//LOAD SCENES
	ResourceManager::InstantiateScene("MainMenuScene", new MainMenuScene("MainMenuScene"));
	ResourceManager::InstantiateScene("FarmScene", new FarmScene("FarmScene"));
	ResourceManager::InstantiateScene("TownScene", new TownScene("TownScene"));

	//LOAD FONTS
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
	catch (std::out_of_range& e) {
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
	catch (std::out_of_range& e) {
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
	catch (std::out_of_range& e) {
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
	catch (std::out_of_range& e) {
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
	catch (std::out_of_range& e) {
		TIM_LOG_ERROR("Font: " << name << " could not be found in resource manager");
		__debugbreak();
	}

	return nullptr;
}
