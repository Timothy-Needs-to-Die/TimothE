#pragma once

#include "pch.h"
#include "Stream.h"

class StreamFile : public IStream
{
public:
	StreamFile();
	virtual ~StreamFile();

	//Reads an amount of data into a buffer of bytes
	virtual int  Read(int bytes, void* pBuffer);
	//Writes an amount of data from a buffer of bytes
	virtual size_t  Write(int bytes, const void* pBuffer);

	//Sets the cursor position for the file
	virtual bool SetCurPos(int pos);

	//Gets the cursor position the file is at currently
	virtual int  GetCurPos();

	//Opens a file for reading
	bool OpenRead(const std::string& filename);

	//Opens a file for writing
	bool OpenWrite(const std::string& filename);

	//Closes a file
	void Close();

private:
	//holds the file that is being edited
	FILE* _pFile;
	bool   _readMode;
	bool   _writeMode;
};

