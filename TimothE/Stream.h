#pragma once

#include <string>

#include "glm.hpp"

class IStream {
public:
	virtual ~IStream() {};

	virtual int Read(int bytes, void* pBuffer) = 0;
	virtual int Write(int bytes, const void* pBuffer) = 0;

	virtual bool SetCurPos(int pos) = 0;
	virtual int GetCurPos() = 0;
};

int ReadInt(IStream& stream);

float ReadFloat(IStream& stream);

glm::vec2 ReadVec2(IStream& stream);


std::string ReadString(IStream& stream);

bool WriteInt(IStream& stream, int n);
bool WriteVec2(IStream& stream, glm::vec2 v);
bool WriteFloat(IStream& stream, float f);
bool WriteString(IStream& stream, const std::string& str);