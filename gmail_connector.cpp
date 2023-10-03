#include "gmail_connector.h"
#include <iostream>
#include <cstdlib>

std::string GmailConnector::fetchEmails(int num_emails) {
    std::string command = "python fetch_emails.py " + std::to_string(num_emails);
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}
