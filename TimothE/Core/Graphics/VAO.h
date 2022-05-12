#pragma once

#include <memory>

#include "VBO.h"
#include "IBO.h"

class VAO
{
public:
	VAO();
	virtual ~VAO();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const std::shared_ptr<VBO>& vertexBuffer);
	void SetIndexBuffer(const std::shared_ptr<IBO>& indexBuffer);

	const std::vector<std::shared_ptr<VBO>>& GetVertexBuffers() const { return _vertexBuffers; }
	const std::shared_ptr<IBO>& GetIndexBuffer() const { return _indexBuffer; }

	static std::shared_ptr<VAO> Create();

private:
	unsigned int _rendererID;
	unsigned int _vertexBufferIndex = 0;
	std::vector<std::shared_ptr<VBO>> _vertexBuffers;
	std::shared_ptr<IBO> _indexBuffer;
};