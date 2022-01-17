#include "Stream.h"

int ReadInt(IStream& stream) {
	int n = 0;
	stream.Read(sizeof(int), (void*)&n);
	return n;
}

float ReadFloat(IStream& stream) {
	float n = 0;
	stream.Read(sizeof(float), (void*)&n);
	return n;
}


std::string ReadString(IStream& stream) {
	int nLength = ReadInt(stream);
	char txt[512];
	stream.Read(nLength, txt);
	return std::string(txt);
}

bool WriteInt(IStream& stream, int n) {
	int numWritten = stream.Write(sizeof(int), &n);
	return (numWritten == sizeof(int));
}

bool WriteFloat(IStream& stream, float f) {
	int numWritten = stream.Write(sizeof(float), &f);
	return (numWritten == sizeof(float));
}

bool WriteString(IStream& stream, const std::string& str) {
	int length = str.length() + 1;
	if (!WriteInt(stream, length)) return false;

	return(stream.Write(length, str.c_str()) == length);
}
