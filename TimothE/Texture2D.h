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
	Texture2D();
	~Texture2D();

	void OnStart() override;
	void OnUpdate() override;
	void OnEnd() override;

	bool Load(char* path, string mode);
	void SetFilterMode(string mode);

	GLuint GetID() const { return _ID; }

	// Inherited via ISerializable
	virtual bool Write(IStream& stream) const override {
		Component::Write(stream);

		return true;

	}
	virtual bool Read(IStream& stream) override {
		Component::Read(stream);


		return true;

	}
	virtual void Fixup() override {

	}
	virtual void DrawEditorUI() override;

private:
	string _UID;
	GLuint _ID;
	// Inherited via Component
	
	// Texture ID
};