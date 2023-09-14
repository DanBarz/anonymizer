#include "anonymizer.h"
#include "splashkit.h"
#include <vector>
#include <string>
#include <regex>
#include <cstdlib> // Include the necessary header for rand

std::vector<anonymized_pattern> patterns;


void initialize_patterns() {
    add_pattern("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}", generate_random_replacement(10));
    add_pattern("\\b\\d{1,4}[-.\\s]?\\d{1,4}[-.\\s]?\\d{1,4}\\b", generate_random_replacement(10));
    add_pattern("\\b\\d{3}[-.\\s]?\\d{3}[-.\\s]?\\d{4}\\b", generate_random_replacement(10));
    add_pattern("\\b\\+?\\d{1,4}[-.\\s]?\\d{1,4}[-.\\s]?\\d{1,4}\\b", generate_random_replacement(10));
    
}

std::string anonymize_text(const std::string inputText, placeholder_data placeholders) {
    string anonymizedText = inputText;

    for (const anonymized_pattern& pattern : patterns) {
        std::regex pattern_regex(pattern.pattern);
        anonymizedText = std::regex_replace(anonymizedText, pattern_regex, pattern.replacement);
    }

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

void add_pattern(const string& pattern, const string& replacement) {
    anonymized_pattern newPattern;
    newPattern.pattern = pattern;
    newPattern.replacement = replacement;
    patterns.push_back(newPattern);
}
