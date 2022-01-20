#include "Console.h"

void Console::Print(string message)
{
	if (output.size() > CONSOLE_MAX_MESSAGES)
	{
		output.erase(output.begin());
	}
	output.push_back(message);
	std::cout << message << std::endl;
}