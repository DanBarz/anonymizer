#include "anonymizer.h"
#include "splashkit.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include "json.hpp" // Include the necessary header for nlohmann/json
// using json = nlohmann::json; // Alias for the JSON library


std::vector<anonymized_pattern> patterns;
const std::string filename = "swapped.json";

void initialize_patterns() {
    add_pattern("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}");
    add_pattern("\\b\\d{1,4}[-.\\s]?\\d{1,4}[-.\\s]?\\d{1,4}\\b");
    add_pattern("\\b\\d{3}[-.\\s]?\\d{3}[-.\\s]?\\d{4}\\b");
    add_pattern("\\b\\+?\\d{1,4}[-.\\s]?\\d{1,4}[-.\\s]?\\d{1,4}\\b");
}

std::string anonymize_text(const std::string inputText, placeholder_data& placeholders) {
    string anonymizedText = inputText;

    // Clear the mapping for the current text
    patterns[0].mapping.clear();

    for (anonymized_pattern& pattern : patterns) {
        std::regex pattern_regex(pattern.pattern);
        auto match_iterator = std::sregex_iterator(inputText.begin(), inputText.end(), pattern_regex);
        auto match_end = std::sregex_iterator();

        while (match_iterator != match_end) {
            std::smatch match = *match_iterator;
            string original = match.str();
            string anonymized = generate_random_replacement(10); // Anonymize data
            anonymizedText = std::regex_replace(anonymizedText, pattern_regex, anonymized);

            // Store original and anonymized data in the mapping
            pattern.mapping[original] = anonymized;

            ++match_iterator;
        }

        // Check if the mapping is not empty before saving it
        if (!pattern.mapping.empty()) {
            // Store the mapping in the placeholder_data struct
            placeholders.mappings.push_back(pattern.mapping);
        }

        // Clear the mapping for the next pattern
        pattern.mapping.clear();
    }

    // Save mappings only once, after processing all patterns
    saveMappingsToJson(placeholders);

    return anonymizedText;
}

string generate_random_replacement(int length) {
    string randomReplacement;

    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (int i = 0; i < length; ++i) {
        randomReplacement += characters[rand() % characters.length()];
    }

    return randomReplacement;
}

void add_pattern(const string& pattern) {
    write_line("Inside add_pattern");
    anonymized_pattern newPattern;
    newPattern.pattern = pattern;
    write_line("Pattern: " + pattern);
    patterns.push_back(newPattern);
    write_line("End of add_pattern");
}

void saveMappingsToJson(const placeholder_data& placeholders) {
    nlohmann::json j;
   
    j["swapped"] = placeholders.mappings;

    std::ofstream file(filename);
    if (file.is_open()) {
        std::cout << "JSON Data: " << j.dump(4) << std::endl;
        file << j.dump(4); 
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    
}
