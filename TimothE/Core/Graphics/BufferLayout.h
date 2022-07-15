#pragma once

#include <vector>
#include <iostream>
#include "../../Core.h"

enum class ShaderDataTypes {
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static unsigned int GetShaderDataTypeSize(ShaderDataTypes type) {
	switch (type) {
	case ShaderDataTypes::Float: return 4;
	case ShaderDataTypes::Float2: return 4 * 2;
	case ShaderDataTypes::Float3: return 4 * 3;
	case ShaderDataTypes::Float4: return 4 * 4;
	case ShaderDataTypes::Mat3: return 4 * 3 * 3;
	case ShaderDataTypes::Mat4: return 4 * 4 * 4;
	case ShaderDataTypes::Int: return 4;
	case ShaderDataTypes::Int2: return 4 * 2;
	case ShaderDataTypes::Int3: return 4 * 3;
	case ShaderDataTypes::Int4: return 4 * 4;
	case ShaderDataTypes::Bool: return 1;
	}

	TIM_LOG_ERROR("Type passed in does not have a size defined");
	return 0;
}

struct BufferElement {
	std::string name;
	ShaderDataTypes type;
	unsigned int size;
	size_t offset;
	bool normalized;

	BufferElement() = default;

	BufferElement(ShaderDataTypes type, const std::string& name, bool normalized = false) :
		name(name), type(type), size(GetShaderDataTypeSize(type)), offset(0), normalized(normalized) {
	}

	unsigned int GetComponentCount() const {
		switch (type) {
		case ShaderDataTypes::Float:	return 1;
		case ShaderDataTypes::Float2:	return 2;
		case ShaderDataTypes::Float3:	return 3;
		case ShaderDataTypes::Float4:	return 4;
		case ShaderDataTypes::Mat3:		return 3;
		case ShaderDataTypes::Mat4:		return 4;
		case ShaderDataTypes::Int:		return 1;
		case ShaderDataTypes::Int2:		return 2;
		case ShaderDataTypes::Int3:		return 3;
		case ShaderDataTypes::Int4:		return 4;
		case ShaderDataTypes::Bool:		return 1;
		}

		TIM_LOG_ERROR("Type passed in does not have a count defined");
	return 0;
	}
};

class BufferLayout {
public:
	BufferLayout() : _stride(12) {}
	BufferLayout(std::initializer_list<BufferElement> elements)
		: _elements(elements) {
		CalculateOffsetsAndStride();
	}

	unsigned int GetStride() const { return _stride; }
	const std::vector<BufferElement>& GetElements() const { return _elements; }

	std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
	std::vector<BufferElement>::iterator end() { return _elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }
private:
	void CalculateOffsetsAndStride() {
		size_t offset = 0;
		_stride = 0;
		for (auto& element : _elements) {
			element.offset = offset;
			offset += element.size;
			_stride += element.size;
		}
	}

	std::vector<BufferElement> _elements;
	unsigned int _stride; 
};
