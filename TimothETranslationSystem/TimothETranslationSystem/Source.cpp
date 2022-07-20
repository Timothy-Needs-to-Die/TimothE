#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B>& p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B>& src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}

int main() {
	std::map<std::string, int> dictionary;
	int index = 0;

	std::ifstream file("SampleDialogue.txt");

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
				if(word == "") continue;

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


	//std::cout << "--------------------------------------------------" << std::endl;
	//for (auto& word : dictionary) {
	//	std::cout << word.second << ":\t" << word.first << std::endl;
	//}

	std::multimap<int, std::string> outputDict = flip_map(dictionary);
	std::cout << "--------------------------------------------------" << std::endl;
	for (auto& word : outputDict) {
		std::cout << word.first << ":\t" << word.second << std::endl;
	}

	for (auto& tl : tokenisedLines) {
		std::cout << tl << std::endl;
	}
}