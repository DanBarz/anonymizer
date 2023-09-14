#ifndef ANONYMIZER_H
#define ANONYMIZER_H
#include "splashkit.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

// Struct to represent placeholder data
struct placeholder_data {
    vector<string> anon_content;
    vector<map<string, string>> mappings;
};

struct anonymized_pattern {
    string pattern;
    string replacement;
};

void initialize_patterns();
std::string anonymize_text(const std::string text, const placeholder_data placeholders);
string generate_random_replacement(int length);
void add_pattern(const string& pattern);

#endif // ANONYMIZER_H
