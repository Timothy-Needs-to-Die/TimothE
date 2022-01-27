#include "Texture2D.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

Texture2D::Texture2D(GameObject* pParent) : Component(pParent), _ID(0)
{
	_UID = UID::GenerateUID();
	SetType(Component::Texture_Type);
	SetCategory(Component::Graphics_Category);
}

Texture2D::Texture2D(std::string path) : Component(), _ID(0)
{
	_UID = UID::GenerateUID();
	SetType(Component::Texture_Type);
	SetCategory(Component::Graphics_Category);

	Load(path);
}

Texture2D::~Texture2D()
{
	//Deletes this texture
	//glDeleteTextures(1, &_ID);
}

void Texture2D::DrawEditorUI()
{
	//displays the texture in the editor window
	ImGui::Text("Texture");
	ImTextureID texID = (void*)_ID;
	//specifies a size of 100x100 for the texture preview
	ImGui::Image(texID, ImVec2(100.0f, 100.0f));

	static std::string texPath = "path";
	ImGui::InputText("##TexturePath", &texPath);
	ImGui::SameLine();
	if (ImGui::Button("Set texture"))
	{
		Load(texPath);
	}
}

// Pass in file path
bool Texture2D::Load(std::string path)
{
	//if (_ID != 0) return true;
	_filePath = path;
	unsigned char* data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);

	if (data != nullptr)
	{
		GenerateTexture(data);
	}
	else
	{
		return false;
	}

	return true;
}

void Texture2D::GenerateTexture(unsigned char* data)
{
	glGenTextures(1, &_ID);

	//Binds the texture so it can be setup
	glBindTexture(GL_TEXTURE_2D, _ID);

	//Setsup the texture
	if (_channels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (_channels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}


	//Set filtering to linear by default
	SetFilterMode("linear");

	//Releases the memory associated with the data
	stbi_image_free(data);
}

void Texture2D::OnStart()
{

}

void Texture2D::OnUpdate(float deltaTime)
{

}

void Texture2D::OnEnd()
{

}

void Texture2D::SetFilterMode(std::string mode)
{
	if (mode == "linear")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (mode == "nearest")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}

// Inherited via ISerializable

inline bool Texture2D::SaveState(IStream& stream) const {
	Component::SaveState(stream);

	//Save filepath
	WriteString(stream, _filePath);

	return true;

}

inline bool Texture2D::LoadState(IStream& stream) {
	Component::LoadState(stream);

	//Loads the texture based on the string that it reads in
	Load(ReadString(stream));

	return true;

}
