#pragma once
#include "pch.h"
#include "BufferLayout.h"

class VBO
{
public:
	VBO(unsigned int size);
	VBO(float* vertices, unsigned int size);
	~VBO();

	static std::shared_ptr<VBO> Create(unsigned int size);
	static std::shared_ptr<VBO> Create(float* vertices, unsigned int size);
	

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, unsigned int size);

	const BufferLayout& GetLayout() const { return _layout; }
	void SetLayout(const BufferLayout& layout) { _layout = layout; }

private:
	unsigned int _rendererID;
	BufferLayout _layout;
};