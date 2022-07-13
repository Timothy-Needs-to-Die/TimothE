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


		int lbPos = l.find_first_of("[");
		int rbPos = l.find_first_of("]");

		std::string characterName = l.substr(lbPos, rbPos + 1);
		tokenisedLine += characterName + ": ";

		int lsPos = l.find_first_of('"');
		int rsPos = l.find_last_of('"');
		std::string eolContent = l.substr(rsPos + 1);

		int aPos;
		std::string filterString = l.substr(rbPos + 1);
		while (aPos = filterString.find('"') != std::string::npos) {
			filterString = filterString.substr(aPos + 1);

			int bPos = filterString.find('"');

			std::string sentence = filterString.substr(0, bPos - 1);

			std::string upperedSentence;
			for (int i = 0; i < sentence.length(); i++) {
				upperedSentence += std::toupper(sentence[i]);
			}
			std::cout << upperedSentence << std::endl;

			std::vector<std::string> brokenSentence;
			std::istringstream ss(upperedSentence);
			std::string token;

			while (std::getline(ss, token, ' ')) {
				int pos;

				pos = token.find('?');
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


				brokenSentence.emplace_back(token);
			}

			for (auto& word : brokenSentence) {
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

				if (dictionary.find(word) == dictionary.end()) {
					dictionary[word] = index;
					tokenisedLine += std::to_string(index) + " ";
					index++;
				}
				else {
					tokenisedLine += std::to_string(dictionary[word]) + " ";
				}
			}

			filterString = filterString.substr(bPos + 1);

		}



		//std::cout << l << std::endl;
		//Turns [Robin]: "Hi Im the town carpenter" into Im the town carpenter
		//std::string sentence = l.substr(lsPos + 1, (rsPos - lsPos) - 1);
		
		tokenisedLine += eolContent;

		tokenisedLines.emplace_back(tokenisedLine);
	}


	std::cout << "--------------------------------------------------" << std::endl;
	for (auto& word : dictionary) {
		std::cout << word.second << ":\t" << word.first << std::endl;
	}

	std::multimap<int, std::string> outputDict = flip_map(dictionary);
	std::cout << "--------------------------------------------------" << std::endl;
	for (auto& word : outputDict) {
		std::cout << word.first << ":\t" << word.second << std::endl;
	}

	for (auto& tl : tokenisedLines) {
		std::cout << tl << std::endl;
	}
}