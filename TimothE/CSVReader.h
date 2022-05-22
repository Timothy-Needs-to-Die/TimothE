#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class CSVReader
{
public:
	static std::vector<std::vector<std::string>> RequestDataFromFile(const std::string& filename);

private:
	static void FindAndReplaceAll(std::string& str, char filter, char replaceWith);

};

