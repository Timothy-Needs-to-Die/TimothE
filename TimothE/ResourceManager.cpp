#include "pch.h"
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
	ResourceManager::InstantiateTexture("character", new Texture2D("Resources/Images/Spritesheets/AlexTest.png", true));
	ResourceManager::InstantiateTexture("spritesheet", new Texture2D("Resources/Images/Spritesheets/RPGpack_sheet.png", true));
	ResourceManager::InstantiateTexture("Button", new Texture2D("Resources/Images/ButtonTest.png"));

	//LOAD SPRITESHEETS
	ResourceManager::InstantiateSpritesheet("testSheet", new SpriteSheet(ResourceManager::GetTexture("spritesheet"), 64, 64));

	//LOAD SHADERS
	ResourceManager::InstantiateShader("ui", new Shader("vr_UIShader.vert", "fr_UIShader.frag"));
	ResourceManager::InstantiateShader("default", new Shader("VertexShader.vert", "FragmentShader.frag"));

	//LOAD SCENES
	ResourceManager::InstantiateScene("CurrentScene", new Scene("Default"));
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