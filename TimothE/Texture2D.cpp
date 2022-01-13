#include "Texture2D.h"
#include <iostream>
#include <fstream>
using namespace std;
Texture2D::Texture2D()
{
	//GLuint tex;
	//glGenTextures(1, &tex);

	//glBindTexture(GL_TEXTURE_2D, tex);

	////Wrapping
	//float color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	////Filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D);

	////Loading texture images
	//float pixels[] = {
	//0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
	//1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	//};
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
	//

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); // Seek to end of file
	fileSize = (int)inFile.tellg(); // Get current position in file - The End. this gives us total file size
	tempTextureData = new char[fileSize]; // Create an new array to store data
	inFile.seekg(0, ios::beg); // Seek back to beginning of file
	inFile.read(tempTextureData, fileSize); // Read in all the data in one go
	inFile.close(); // Close the file

	cout << path << " loaded." << endl;

	glGenTextures(1, &_ID); // Get next Texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); // Bind the texture to the ID
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	delete[] tempTextureData; // Clear up the data - we don't need this anymore
	return true;
}