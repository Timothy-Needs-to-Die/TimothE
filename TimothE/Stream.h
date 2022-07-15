#pragma once

#include "pch.h"

#include "glm.hpp"

class IStream {
public:
	virtual ~IStream() {};

	virtual int Read(int bytes, void* pBuffer) = 0;
	virtual size_t Write(int bytes, const void* pBuffer) = 0;

	virtual bool SetCurPos(int pos) = 0;
	virtual int GetCurPos() = 0;
};

//Read operations
int ReadInt(IStream& stream);
float ReadFloat(IStream& stream);
std::string ReadString(IStream& stream);
glm::vec2 ReadVec2(IStream& stream);
glm::vec4 ReadVec4(IStream& stream);

//Write operations
bool WriteInt(IStream& stream, int n);
bool WriteFloat(IStream& stream, float f);
bool WriteString(IStream& stream, const std::string& str);
bool WriteVec2(IStream& stream, glm::vec2 v);
bool WriteVec4(IStream& stream, glm::vec4 v);