#pragma once

#include "pch.h"

#define CONSOLE_MAX_MESSAGES 500

class Console
{
public:
	static void Print(std::string message);
	static std::vector<std::string> GetConsoleOutput() { return output; }

private:
	static std::vector<std::string> output;
};