#pragma once

#include "pch.h"

class IBO
{
public:
	IBO(unsigned int* indices, unsigned int count);
	~IBO();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const { return _count; }

	static std::shared_ptr<IBO> Create(unsigned int* indices, unsigned int count);

private:
	unsigned int _rendererID;
	unsigned int _count;
};

