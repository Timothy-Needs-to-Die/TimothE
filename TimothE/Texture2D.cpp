#include "Texture2D.h"
#include "imgui.h"

Texture2D::Texture2D() : Component()
{
	_UID = UID::GenerateUID();
	SetType(Component::Texture_Type);
	SetCategory(Component::Graphics_Category);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

void Texture2D::DrawEditorUI()
{
	ImGui::Text("Texture");
	ImTextureID texID = (void*)_ID;
	ImGui::Image(texID, ImVec2(100.0f, 100.0f));
}

// Pass in file path, filter mode as "linear" or "nearest"
bool Texture2D::Load(string path, string mode)
{
	_filePath = path;
	_ID = SOIL_load_OGL_texture
	(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	/* check for an error during the load process */
	if (_ID == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	return true;
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _ID);
}

void Texture2D::OnStart() 
{ 

}

void Texture2D::OnUpdate()
{ 

}

void Texture2D::OnEnd()
{ 

}

void Texture2D::SetFilterMode(string mode)
{
	if (mode == "linear")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		cout << "Linear filter mode" << endl;
	}
	else if (mode == "nearest")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		cout << "Nearest filter mode" << endl;
	}
}