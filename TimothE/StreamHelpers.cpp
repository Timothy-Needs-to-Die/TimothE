#include "Stream.h"


//reads data from the stream and interprets it as a int
int ReadInt(IStream& stream) {
	int n = 0;
	stream.Read(sizeof(int), (void*)&n);
	return n;
}

//reads data from the stream and interprets it as a float
float ReadFloat(IStream& stream) {
	float n = 0;
	stream.Read(sizeof(float), (void*)&n);
	return n;
}

//reads data from the stream and interprets it as a string
std::string ReadString(IStream& stream) {
	//Get the length of the string first (saved when the string is saved)
	int nLength = ReadInt(stream);
	char txt[512];
	stream.Read(nLength, txt);
	return std::string(txt);
}

//reads data from the stream and interprets it as a glm::vec2 (this performs two ReadFloat operations)
glm::vec2 ReadVec2(IStream& stream) {
	glm::vec2 v;
	v.x = ReadFloat(stream);
	v.y = ReadFloat(stream);
	return v;
}

glm::vec4 ReadVec4(IStream& stream)
{
	glm::vec4 v;
	v.x = ReadFloat(stream);
	v.y = ReadFloat(stream);
	v.z = ReadFloat(stream);
	v.w = ReadFloat(stream);

	return v;
}

//writes an integer to the stream
bool WriteInt(IStream& stream, int n) {
	int numWritten = stream.Write(sizeof(int), &n);
	return (numWritten == sizeof(int));
}

//writes a float to the stream
bool WriteFloat(IStream& stream, float f) {
	int numWritten = stream.Write(sizeof(float), &f);
	return (numWritten == sizeof(float));
}

//Writes a string to the stream
bool WriteString(IStream& stream, const std::string& str) {
	//Gets the length of the string and add 1 to it.
	int length = str.length() + 1;
	//if saving the length is not successful then return
	if (!WriteInt(stream, length)) return false;

	//Write the string provided that the int length of the string saved
	return(stream.Write(length, str.c_str()) == length);
}

//Writes a glm::vec2 to the stream (this performs two WriteFloat operations)
bool WriteVec2(IStream& stream, glm::vec2 v) {
	return(WriteFloat(stream, v.x) && WriteFloat(stream, v.y));
}

bool WriteVec4(IStream& stream, glm::vec4 v)
{
	return WriteFloat(stream, v.x) && WriteFloat(stream, v.y) && WriteFloat(stream, v.z) && WriteFloat(stream, v.w);
}
