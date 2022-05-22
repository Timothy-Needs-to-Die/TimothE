#include "Console.h"

void Console::Print(std::string message)
{
	if (output.size() > CONSOLE_MAX_MESSAGES)
	{
		output.erase(output.begin());
	}
	output.push_back(message);
	std::cout << message << "\n";
}