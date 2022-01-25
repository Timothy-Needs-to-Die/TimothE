#pragma once

#include "pch.h"

#include "UID.h"
#include "Component.h"

#include "SOIL/stb_image.h"

class Texture2D : public Component
{
public:
	Texture2D(GameObject* pParent);
	Texture2D(std::string path);
	~Texture2D();

	COMPONENT_STATIC_TYPE(Texture_Type)

	//Inherited Component methods
	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;
	void DrawEditorUI() override;

	//Getters
	int GetHeight() { return _height; };
	int GetWidth() { return _width; };
	GLuint GetID() const { return _ID; }

	//Sets the filter mode for the texture
	void SetFilterMode(std::string mode);

	//Loads an image from file into a texture. Returns true if successful or false if not
	bool Load(std::string path);

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override;
	virtual bool LoadState(IStream& stream) override;

	void Bind(int slot) {
		glBindTextureUnit(slot, _ID);
	}

private:
	void GenerateTexture(unsigned char* data);

	std::string _filePath;
	std::string _UID;
	
	//texture ID
	GLuint _ID; 

	int _width;
	int _height;
	int _channels;
};