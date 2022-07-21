#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include "CSVReader.h"
#include "Dirent.h"


//TODO: Write more dialogs files
//TODO: Read in all dialog files 
//TODO: Output all tokened files
//TODO: Documentation


int main() {
	std::map<std::string, int> dictionary;


	std::map<int, std::string> inputDict;
	std::map<int, std::string> outputDict;
	std::vector<std::vector<std::string>> dictionaryContents = CSVReader::RequestDataFromFile("Dictionary.csv");


	int lastRow;
	int index = 0;
	for (auto& line : dictionaryContents)
	{
		if (index == 0) {
			index++;
			continue;
		}
		int t = std::stoi(line[0]);
		std::string word = line[1];

		inputDict[t] = word;
		index++;
	}

	for (auto& p : inputDict) {
		dictionary[p.second] = p.first;
	}

	lastRow = index;

	DIR* directory = opendir("./Dialog/");
	struct dirent* dirent;
	if (directory)
	{
		while ((dirent = readdir(directory)) != NULL)
		{
			if (dirent->d_type == 32768)
			{
				std::string fn = "Dialog/" + std::string(dirent->d_name);
				std::ifstream file(fn);

				std::vector<std::string> lines;
				std::vector<std::string> tokenisedLines;


				std::stringstream fileStream;

				fileStream << file.rdbuf();

				std::string line;
				while (std::getline(fileStream, line, '\n'))
				{
					lines.emplace_back(line);
				}

				for (auto& l : lines) {
					std::string tokenisedLine;

					int leftBracePos = l.find_first_of("[");
					int rightBracePos = l.find_first_of("]");

					std::string characterName = l.substr(leftBracePos, rightBracePos + 1);
					tokenisedLine += characterName + ": ";

					int lastSpeechMark = l.find_last_of('"');
					std::string eolContent = l.substr(lastSpeechMark + 1);

					int markAPos;
					std::string filterString = l.substr(rightBracePos + 2);
					while (markAPos = filterString.find('"') != std::string::npos) {

						filterString = filterString.substr(markAPos - 1);

						int markBPos = filterString.find('"');

						std::string sentence = filterString.substr(0, markBPos);

						if (sentence == "") {
							continue;
						}

						//Converts hello world to HELLO WORLD
						std::string upperedSentence;
						for (int i = 0; i < sentence.length(); i++) {
							upperedSentence += std::toupper(sentence[i]);
						}

						//Converts HELLO WORLD to a vector of (HELLO), (WORLD). Also parses punctuation
						std::vector<std::string> brokenSentence;
						std::istringstream ss(upperedSentence);
						std::string token;

						while (std::getline(ss, token, ' ')) {
							int pos = token.find('?');
							if (pos != std::string::npos)
							{
								token = token.substr(0, pos);
								brokenSentence.emplace_back("?");
							}
							pos = token.find('.');
							if (pos != std::string::npos) {
								token = token.substr(0, pos);
								brokenSentence.emplace_back(".");
							}

							//Places the token into the broken sentence list
							brokenSentence.emplace_back(token);
						}

						//Cycles through all tokens
						for (auto& word : brokenSentence) {
							if (word.empty()) continue;

							//If the word is game data then it is added to the tokenised line and the next word is checked
							if (word[0] == '#') {
								tokenisedLine += word + " ";
								continue;
							}
							else if (word[0] == '~') {
								tokenisedLine += word + " ";
								continue;
							}
							else if (word[0] == '[') {
								tokenisedLine += word + " ";
								continue;
							}
							else if (word[0] == '-') {
								tokenisedLine += word + " ";
								continue;
							}

							//If the word cannot be found in our dictionary
							if (dictionary.find(word) == dictionary.end()) {
								dictionary[word] = index; //Add this word to the dictionary with our new index
								tokenisedLine += std::to_string(index) + " "; //Adds this index to the tokenised line
								index++; //Increments our index
							}
							else {
								tokenisedLine += std::to_string(dictionary[word]) + " "; //Adds this words token to the line
							}
						}


						filterString = filterString.substr(markBPos + 1);
						markAPos = filterString.find('"');

					}

					tokenisedLine += eolContent;

					tokenisedLines.emplace_back(tokenisedLine);
				}


				for (auto& el : dictionary) {
					outputDict[el.second] = el.first;
				}

				
				std::ofstream output("TranslatedDialog/" + std::string(dirent->d_name));

				for (auto& tl : tokenisedLines) {
					std::cout << tl << std::endl;
					output << tl << "\n";
				}
			}
		}
		closedir(directory);
	}


	std::cout << "--------------------------------------------------" << std::endl;
	for (auto& word : outputDict) {
		std::cout << word.first << ":\t" << word.second << std::endl;
	}


	std::ofstream outDictFile("Dictionary.csv");

	if (dictionaryContents.empty()) {
		std::vector<std::string> nl;
		nl.emplace_back("Index");
		nl.emplace_back("English");
		nl.emplace_back("French");
		nl.emplace_back("Spanish");
		nl.emplace_back("Italian");
		nl.emplace_back("German");

		dictionaryContents.emplace_back(nl);
	}

	for (int i = 0; i < dictionaryContents[0].size(); i++) {
		outDictFile << dictionaryContents[0][i] << ",";
	}
	outDictFile << "\n";

	for (int i = 1; i < dictionaryContents.size(); i++) {
		for (int j = 0; j < dictionaryContents[i].size(); j++) {
			outDictFile << dictionaryContents[i][j] << ",";
		}
		outDictFile << "\n";
	}

	for (int i = lastRow; i < index; i++) {
		outDictFile << i << "," << outputDict[i] << "\n";
	}

	outDictFile.close();
}