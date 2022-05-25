#include "ResourceManager.h"
#include "Core/Graphics/OpenGLError.h"
#include "FarmScene.h"
#include "Dirent.h"
#include "misc/cpp/imgui_stdlib.h"

#include "FarmScene.h"
#include "TownScene.h"

std::map<std::string, Texture2D*> ResourceManager::_textures;
std::map<std::string, Shader*> ResourceManager::_shaders;
std::map<std::string, Scene*> ResourceManager::_scenes;
std::map<std::string, SpriteSheet*> ResourceManager::_spritesheets;
std::map<std::string, Font*> ResourceManager::_fonts;

std::string ResourceManager::_UID;

void ResourceManager::Init()
{
	_UID = UID::GenerateUID();

	//LOAD TEXTURES
	ResourceManager::InstantiateTexture("lenna", new Texture2D("lenna3.jpg"));
	ResourceManager::InstantiateTexture("fish", new Texture2D("Fish.png"));
	ResourceManager::InstantiateTexture("character", new Texture2D("Resources/Images/Spritesheets/EnemySpritesheet.png", true));
	ResourceManager::InstantiateTexture("spritesheet", new Texture2D("Resources/Images/Spritesheets/RPGpack_sheet.png", true));
	ResourceManager::InstantiateTexture("medispritesheet", new Texture2D("Resources/Images/Spritesheets/MediSprites.png", true));
	ResourceManager::InstantiateTexture("roguespritesheet", new Texture2D("Resources/Images/Spritesheets/RogueSprites.png", true));
	ResourceManager::InstantiateTexture("itemspritesheet", new Texture2D("Resources/Images/Spritesheets/ItemsSheet.png", true));
	ResourceManager::InstantiateTexture("animalspritesheet", new Texture2D("Resources/Images/Spritesheets/AnimalSheet.png", true));
	ResourceManager::InstantiateTexture("extraspritesheet", new Texture2D("Resources/Images/Spritesheets/ExtraSpriteSheet.png", true));
	ResourceManager::InstantiateTexture("buildspritesheet", new Texture2D("Resources/Images/Spritesheets/BuildingSheet.png", true));
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


	//LOAD SPRITESHEETS
	ResourceManager::InstantiateSpritesheet("spritesheet", new SpriteSheet(ResourceManager::GetTexture("spritesheet"), 64, 64, "spritesheet"));
	ResourceManager::InstantiateSpritesheet("medispritesheet", new SpriteSheet(ResourceManager::GetTexture("medispritesheet"), 64, 64, "medispritesheet"));
	ResourceManager::InstantiateSpritesheet("itemspritesheet", new SpriteSheet(ResourceManager::GetTexture("itemspritesheet"), 128, 128, "itemspritesheet"));
	ResourceManager::InstantiateSpritesheet("roguespritesheet", new SpriteSheet(ResourceManager::GetTexture("roguespritesheet"), 17, 17, "roguespritesheet"));
	ResourceManager::InstantiateSpritesheet("animalspritesheet", new SpriteSheet(ResourceManager::GetTexture("animalspritesheet"), 32, 32, "animalspritesheet"));
	ResourceManager::InstantiateSpritesheet("extraspritesheet", new SpriteSheet(ResourceManager::GetTexture("extraspritesheet"), 15, 15, "extraspritesheet"));
	ResourceManager::InstantiateSpritesheet("buildspritesheet", new SpriteSheet(ResourceManager::GetTexture("buildspritesheet"), 32, 32, "buildspritesheet"));
	ResourceManager::InstantiateSpritesheet("swords", new SpriteSheet(ResourceManager::GetTexture("swords"), 16, 16, "swords"));
	ResourceManager::InstantiateSpritesheet("axes", new SpriteSheet(ResourceManager::GetTexture("axes"), 16, 16, "axes"));
	ResourceManager::InstantiateSpritesheet("pickaxes", new SpriteSheet(ResourceManager::GetTexture("pickaxes"), 16, 16, "pickaxes"));
	ResourceManager::InstantiateSpritesheet("planks", new SpriteSheet(ResourceManager::GetTexture("planks"), 64, 64, "pickaxes"));

	//LOAD SHADERS
	ResourceManager::InstantiateShader("ui", new Shader("vr_UIShader.vert", "fr_UIShader.frag"));
	ResourceManager::InstantiateShader("default", new Shader("VertexShader.vert", "FragmentShader.frag"));

	//LOAD SCENES
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
	std::ofstream fileStream("./fonts");
	_fonts.clear();
	DIR* directory = opendir("./fonts");
	struct dirent* dirent;
	if (directory)
	{
		while ((dirent = readdir(directory)) != NULL)
		{
			if (dirent->d_type == 32768)
			{
				InstantiateFont(dirent->d_name, new Font(dirent->d_name));

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