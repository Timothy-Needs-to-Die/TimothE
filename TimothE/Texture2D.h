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
	~Texture2D();

	COMPONENT_STATIC_TYPE(Texture_Type)

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	bool Load(string path, string mode);
	void Bind();
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

		Load(ReadString(stream), "");

		return true;

	}

	virtual void DrawEditorUI() override;

private:
	string _filePath;
	string _UID;
	GLuint _ID;

	// Texture ID
};
