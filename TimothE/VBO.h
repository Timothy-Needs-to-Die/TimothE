#pragma once
class VBO
{
public:
	VBO() { };
	~VBO();
public:
	//Create Buffer
	void CreateVBO();

	//Get Buffer ID
	unsigned int GetVertexBufferID() { return _ID; };
private:
	unsigned int _ID = 0;
};