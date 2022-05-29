#include "pch.h"
#include "Bed.h"

#include "CSVReader.h"
#include "Core.h"

std::vector<std::vector<std::string>> CSVReader::RequestDataFromFile(const std::string& filename)
{
    //Open file at given location
    std::ifstream file = std::ifstream(filename);

    //Early out in case file does not exist
    if (!file.good()) {
        TIM_LOG_ERROR("file at: " << filename << " does not exist");
        return std::vector<std::vector<std::string>>();
    }

    //Return result
    std::vector<std::vector<std::string>> result;

    //Storing the index allows us to skip the first line (Headers)
    int index = 0;

    //store the current line
    std::string line;
    while (std::getline(file, line)) {
        //Skips the first line
        if (index == 0) {
            index++;
            continue;
        }

        //load the new line into a string stream
        std::stringstream sstr(line);

        //Store the contents of that line in a vector
        std::vector<std::string> row;

        //Store the content 
        std::string content;

        //split the line by each comma
        while (std::getline(sstr, content, ',')) {
            //Finds and replace all ` with , (Recursive function)
            FindAndReplaceAll(content, '`', ',');
            
            //Places content into row
            row.emplace_back(content);
        }

        //Places row into result 
        result.emplace_back(row);
    }

    return result;
}

void CSVReader::FindAndReplaceAll(std::string& str, char filter, char replaceWith)
{
	//find location of the filter char
    int location = str.find(filter);

	//if we have a location
    if (location != std::string::npos) {
		//replace the filter with the new character
        str = str.replace(location, 1, 1, replaceWith);

		//recall this method
        FindAndReplaceAll(str, filter, replaceWith);
    }
}
