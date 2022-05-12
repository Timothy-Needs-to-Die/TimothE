#pragma once
class RBO
{
public:
	RBO() { };
	~RBO();
public:
	//Create Buffer
	void CreateRBO();

	//Depth Stencil Initialization
	void AddDepthStencil();

	//Get Buffer ID
	unsigned int GetRenderBufferID() { return _ID; };
private:
	unsigned int _ID = 0;
};