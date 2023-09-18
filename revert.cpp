#include "revert.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using json2 = nlohmann::json;

// The filename of the JSON file containing the mappings
const std::string filename = "swapped.json";

// Function to load mappings from JSON
void loadMappingsFromJson(placeholder_data& placeholders) {

    // Open the JSON file
    std::ifstream file(filename);

    // If the file is open, read the JSON data
    if (file.is_open()) {
        nlohmann::json j;
        file >> j;
        file.close();

        if (j.find("swapped") != j.end()) {
            auto swapped = j["swapped"];
            for (const auto& mapping : swapped) {
                std::map<std::string, std::string> reversedMapping;
                for (auto it = mapping.begin(); it != mapping.end(); ++it) {
                    reversedMapping[it.value()] = it.key();
                }
                placeholders.mappings.push_back(reversedMapping);
            }
        }
    } else {

        // If the file is not open, print an error message
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

// Process CSV data using the mapping and write to a new CSV file
void processCSVWithMapping(const std::string& inputFilename, const std::string& outputFilename, const std::vector<std::map<std::string, std::string>>& mappings) {
    
    // Open the input and output files
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);

    // If the files are open, read the input file line by line and write to the output file
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input or output file." << std::endl;
        return;
    }

    std::string line;
    // Iterate through each line of the input file
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string field;
        bool firstField = true;

        // Iterate through each field of the line
        while (std::getline(iss, field, ',')) {
            std::istringstream fieldStream(field);
            std::string word;
            std::string newField;
            bool firstWord = true;

            // Iterate through each word of the field
            while (fieldStream >> word) {
                if (word.front() == '\"' && word.back() == '\"') {
                    word = word.substr(1, word.size() - 2);
                }

                // Remove non-alphanumeric characters from the word
                word.erase(std::remove_if(word.begin(), word.end(), [](char c) { return !std::isalnum(c); }), word.end());

                // Confirm that the word is 10 characters long
                bool wordFoundInMapping = false;
                if (word.size() == 10) {
                    for (const auto& mapping : mappings) {
                        auto it = mapping.find(word);
                        
                        // If the word is found in the mapping, replace it with the corresponding value
                        if (it != mapping.end()) {
                            std::cout << "Word '" << word << "' found in mapping. Replacing with '" << it->second << "'\n";  // Debug statement
                            word = it->second;
                            wordFoundInMapping = true;
                            break;
                        }
                    }
                }

                // If the word is not found in the mapping, print an error message
                if (!wordFoundInMapping) {
                    std::cout << "Word '" << word << "' not found in any mapping.\n";  // Debug statement
                }

                // Add the word to the new field
                if (firstWord) {
                    newField = word;
                    firstWord = false;
                } else {
                    newField += " " + word;
                }
            }

            // Add the new field to the output file
            if (!firstField) {
                outputFile << ",";
            }

            // If the new field is empty, add a placeholder
            outputFile << "\"" << newField << "\"";
            firstField = false;
        }
        outputFile << std::endl;
    }

    inputFile.close();
    outputFile.close();
}