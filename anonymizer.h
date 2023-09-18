#ifndef ANONYMIZER_H
#define ANONYMIZER_H

#include "splashkit.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

// Struct to represent placeholder data
struct placeholder_data {
    vector<std::string> anon_content;
    vector<map<std::string, std::string>> mappings; // Store original -> anonymized mappings
};

// Struct to represent a pattern
struct anonymized_pattern {
    string pattern;
    map<string, string> mapping; // Store original -> anonymized mapping
};

// Initialize the patterns
void initialize_patterns();

// Anonymizes the string and maps the original data to the anonymized data
std::string anonymize_text(const std::string inputText, placeholder_data& placeholders);

// Generates a random replacement string
string generate_random_replacement(int length);

// Adds a pattern to the patterns vector
void add_pattern(const string& pattern);

// Saves the mappings to a JSON file
void saveMappingsToJson(const placeholder_data& placeholders);

#endif // ANONYMIZER_H
