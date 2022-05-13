#pragma once

#include <string>
#include <iostream>
#include <sstream>


static class Tag 
{
	
public:
	static std::string _tags[32];

	static void AddTag(const std::string& tagName);
	static void RemoveTag(const std::string& tagName);
	static bool CheckTag(const std::string& tagName);

	static void PrintTags();
};