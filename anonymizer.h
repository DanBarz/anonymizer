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

struct anonymized_pattern {
    string pattern;
    map<string, string> mapping; // Store original -> anonymized mapping
};

void initialize_patterns();
std::string anonymize_text(const std::string inputText, placeholder_data& placeholders);
string generate_random_replacement(int length);
void add_pattern(const string& pattern);
void saveMappingsToJson(const placeholder_data& placeholders);

#endif // ANONYMIZER_H

// #ifndef ANONYMIZER_H
// #define ANONYMIZER_H
// #include "splashkit.h"
// #include <string>
// #include <vector>
// #include <map>
// using namespace std;

// // Struct to represent placeholder data
// struct placeholder_data {
//     vector<string> anon_content;
//     vector<map<string, string>> mappings;
// };

// struct anonymized_pattern {
//     string pattern;
//     string replacement;
// };

// void initialize_patterns();
// std::string anonymize_text(const std::string text, const placeholder_data placeholders);
// string generate_random_replacement(int length);
// void add_pattern(const string& pattern);

// #endif // ANONYMIZER_H
// x