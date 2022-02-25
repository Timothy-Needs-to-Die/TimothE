#include "Console.h"

void Console::Print(std::string message)
{
	if (output.size() > CONSOLE_MAX_MESSAGES)
	{
		output.erase(output.begin());
	}
	output.push_back(message);
	std::cout << message << std::endl;
}

void Console::EditorUI()
{
	ImGui::Begin("Console", 0, ImGuiWindowFlags_NoMove);

	// get output from console class
	std::vector<std::string> consoleOut = Console::GetConsoleOutput();
	// convert vector to string array
	std::string* out = &consoleOut[0];
	if (out != nullptr)
	{
		// output as wrapped text
		ImGui::TextWrapped(out->c_str());

		// scroll to the bottom of the console window
		ImGui::SetScrollY(ImGui::GetScrollMaxY());
	}

	ImGui::End();
}
