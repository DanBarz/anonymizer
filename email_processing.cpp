#include <fstream>
#include <string>
#include <iostream>
#include "json.hpp"
#include "splashkit.h" // Include SplashKit
#include "email_processing.h"
 
using json_custom = nlohmann::json;
using namespace std;

// Function to read email content from data.json
vector<email_content> read_data_from_json(const std::string &filename) {
    vector<email_content> emailData;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return emailData;
    }

    json_custom jsonData; // Use your custom json type
    file >> jsonData;
    file.close();

    for (const auto &entry : jsonData) {
        email_content email;
        email.from = entry["from"];
        email.to = entry["to"];
        email.subject = entry["subject"];
        email.content = entry["content"];

        emailData.push_back(email);
    }

    return emailData;
}

// Function to save email content to a JSON file
void save_data_to_json(const std::string &filename, const vector<email_content> &emailData) {
    json_custom jsonData; // Use your custom json type

    for (const email_content &email : emailData) {
        json_custom entry;
        entry["from"] = email.from;
        entry["to"] = email.to;
        entry["subject"] = email.subject;
        entry["content"] = email.content;

        jsonData.push_back(entry);
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for writing" << endl;
        return;
    }

    file << jsonData.dump(4); // Pretty-print with 4 spaces of indentation
    file.close();
}
