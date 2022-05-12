#pragma once 
#include "Serializable.h"
#include <string>
#include <iostream>

static class Tag : public ISerializable
{
	
public:
	static std::string _tags[32];

	static void AddTag(const std::string& tagName);
	static void RemoveTag(const std::string& tagName);
	static bool CheckTag(const std::string& tagName);

	static void PrintTags();

private: 
	

};