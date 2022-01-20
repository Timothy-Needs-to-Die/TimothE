#pragma once
#include <gl/glew.h>
#include <iostream>
#include <fstream>

#include "UID.h"
#include "Component.h"

#include "SOIL/SOIL2.h"
#include "SOIL/stb_image.h"
#include "SOIL/image_helper.h"

using namespace std;

class Texture2D : public Component
{
public:
	Texture2D(GameObject* pParent);
	Texture2D(string path);
	~Texture2D();

	COMPONENT_STATIC_TYPE(Texture_Type)

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	int GetHeight() { return _height; };
	int GetWidth() { return _width; };

	bool Load(string path);
	void SetFilterMode(string mode);

	GLuint GetID() const { return _ID; }

	// Inherited via ISerializable
	virtual bool SaveState(IStream& stream) const override {
		Component::SaveState(stream);

		WriteString(stream, _filePath);

		return true;

	}
	virtual bool LoadState(IStream& stream) override {
		Component::LoadState(stream);

		Load(ReadString(stream));

		return true;

	}

	virtual void DrawEditorUI() override;

private:
	void GenerateTexture(unsigned char* data);

	string _filePath;
	string _UID;
	GLuint _ID;

	int _width;
	int _height;
	int _channels;
	// Texture ID
};
