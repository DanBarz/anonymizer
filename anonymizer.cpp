#include "anonymizer.h"
#include "splashkit.h"
#include <vector>
#include <string>
#include <regex>
#include <cstdlib> // Include the necessary header for rand



void initialize_patterns(vector<anonymized_pattern> &patterns) {
    add_pattern("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}", patterns);
    add_pattern("\\b\\d{1,4}[-.\\s]?\\d{1,4}[-.\\s]?\\d{1,4}\\b", patterns);
    add_pattern("\\b\\d{3}[-.\\s]?\\d{3}[-.\\s]?\\d{4}\\b", patterns);
    add_pattern("\\b\\+?\\d{1,4}[-.\\s]?\\d{1,4}[-.\\s]?\\d{1,4}\\b", patterns);
}

std::string anonymize_text(const std::string inputText, const std::vector<anonymized_pattern>& patterns) {
    std::string anonymizedText = inputText;

    for (const anonymized_pattern& pattern : patterns) {
        write_line("this is inside the anonymize_text function");
        std::regex pattern_regex(pattern.pattern);
        write_line("Pattern: " + pattern.pattern + " Replacement: " + pattern.replacement); 
        anonymizedText = std::regex_replace(anonymizedText, pattern_regex, pattern.replacement);
        write_line("Pattern: " + pattern.pattern + " Replacement: " + pattern.replacement);
    }

    return anonymizedText;
}

void add_pattern(const string& pattern, vector<anonymized_pattern>& patterns) {
    write_line("This is inside the add_pattern function");
    anonymized_pattern newPattern;
    newPattern.pattern = pattern;
    // You can access the replacement from the struct
    write_line("Adding pattern: " + pattern + " with replacement: " + newPattern.replacement);
    patterns.push_back(newPattern);
}
