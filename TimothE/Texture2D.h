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

	int GetCategory() const override { return 0; };
	int GetType() const override { return _type; };

	bool Load(char* path, string mode);
	void SetFilterMode(string mode);

	GLuint GetID() const { return _ID; }
private:
	string _UID;
	GLuint _ID; // Texture ID
};