#pragma once
class VAO
{
public:
	VAO() { };
	~VAO();
public:
	//Create Buffer
	void CreateVAO();

	//Bind/Unbind Buffer
	void BindBuffer();
	void UnbindBuffer();

	//Get Buffer ID
	unsigned int GetVertexArrayID() { return _ID; };
private:
	unsigned int _ID = 0;
};