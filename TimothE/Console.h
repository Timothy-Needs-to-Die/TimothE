#pragma once

#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::vector;

#define CONSOLE_MAX_MESSAGES 500

class Console
{
public:
	static void Print(string message);
	static vector<string> GetConsoleOutput() { return output; }

private:
	static vector<string> output;
};