#ifndef REVERT_H
#define REVERT_H
#include "anonymizer.h"

#include <map>
#include <vector>
#include <string>

// Function to load mappings from JSON
void loadMappingsFromJson(placeholder_data& placeholders);

// Function to process CSV data using the mapping and write to a new CSV file
void processCSVWithMapping(const std::string& inputFilename, const std::string& outputFilename, const std::vector<std::map<std::string, std::string>>& mappings);

#endif // REVERT_H
