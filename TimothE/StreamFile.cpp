#include "pch.h"
#include "StreamFile.h"

StreamFile::StreamFile()
	: _pFile(NULL), _readMode(false), _writeMode(false) {}


StreamFile::~StreamFile()
{
	//Closes the file automatically upon object deletion
	Close();
}


bool StreamFile::OpenRead(const std::string& filename)
{
	//If we do not have a file then return false
	if (_pFile != NULL)
		return false;

	//opens the file for a read operations
	_pFile = fopen(filename.c_str(), "r");

	//Assigns read mode if we now have a open file
	_readMode = (_pFile != NULL);
	return _readMode;
}


bool StreamFile::OpenWrite(const std::string& filename)
{
	//if we do not have a file then return false
	if (_pFile != NULL)
		return false;

	//Opens the file for writing
	_pFile = fopen(filename.c_str(), "w");

	//Assigns write mode if we now have a open file
	_writeMode = (_pFile != NULL);
	return _writeMode;
}

void StreamFile::Close()
{
	//if we have a open file then close it
	if (_pFile != NULL)
		fclose(_pFile);

	//Sets write and read mode to false
	_writeMode = false;
	_readMode = false;
}


int StreamFile::Read(int bytes, void* pBuffer)
{
	//Asserts that our buffer has some data
	assert(pBuffer != NULL);

	//If we are not in read mode then return nothing
	if (!_readMode)
		return 0;

	//Read the amount of data requested from the file
	return fread(pBuffer, 1, bytes, _pFile);
}


int StreamFile::Write(int bytes, const void* pBuffer)
{
	//Asserts that we have a buffer
	assert(pBuffer != NULL);

	//If we are not in write mode then return nothing
	if (!_writeMode)
		return 0;

	//Write the amount of data to the buffer
	return fwrite(pBuffer, 1, bytes, _pFile);
}


bool StreamFile::SetCurPos(int pos)
{
	//If we are not in read mode and not in write mode then return false
	if (!_readMode && !_writeMode)
		return false;

	//Seek to the position passed in
	return (fseek(_pFile, pos, SEEK_SET) == 0);
}


int StreamFile::GetCurPos()
{
	//If we are not in read mode and not in write mode then return false
	if (!_readMode && !_writeMode)
		return 0;

	//Get the current cursor position
	return ftell(_pFile);
}

