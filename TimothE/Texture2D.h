#pragma once
#include <gl/glew.h>
#include <iostream>
#include <fstream>
#include "SOIL/SOIL2.h"
#include "UID.h"

using namespace std;

class Texture2D
{
private:
	string _UID;
	GLuint _ID; // Texture ID

public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, string mode);
	void SetFilterMode(string mode);

	GLuint GetID() const { return _ID; }
};