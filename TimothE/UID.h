#pragma once

#include "pch.h"

/*
UUIDs are written in 5 groups of hexadecimal digits separated by hyphens.
The length of each group is: 8-4-4-4-12. UUIDs are fixed length.
For example: 123e4567-e89b-12d3-a456-426655440000
This system uses the first eight characters as time since time began minimising the risk of equal ids.
*/

class UID {
public:
	static void Init() {
		srand((unsigned int)time(NULL));
	}

	static std::string GenerateUID() {
		std::string uuid;

		//convert the current system time to string
		std::string castedResult = std::to_string(std::time(nullptr));

		//Gets the last eight characters
		std::string lastEight = castedResult.substr(2, 8);

		//Adds the time to the string stream in hexidecimal format
		std::stringstream ss;
		ss << std::hex << std::stoi(lastEight);

		uuid += ss.str();

		uuid += GenerateSequence(8 % ss.str().length());
		uuid += '-';

		uuid += GenerateSequence(4);
		uuid += '-';

		uuid += GenerateSequence(4);
		uuid += '-';

		uuid += GenerateSequence(4);
		uuid += '-';

		uuid += GenerateSequence(12);

		castedResult.clear();
		lastEight.clear();

		return uuid;
	}

private:
	static std::string GenerateSequence(int length) {
		//Stores the hexidecimal characters
		char characters[16] = {
			'0', '1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'
		};


		//Holds the sequence
		std::string sequence;

		//Generates a character for each length
		for (int i = 0; i < length; i++) {
			int index = rand() % 16;
			sequence += characters[index];
		}

		return sequence;
	}
};
