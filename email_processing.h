#ifndef EMAIL_PROCESSING
#define EMAIL_PROCESSING
#include "splashkit.h"
#include <string>

struct email_content {
    std::string from;
    std::string content;
    std::string subject;
    std::string to;
};

void display_anonymized_text(const std::string& text);
vector<email_content> read_data_from_json(const std::string &filename);
void save_data_to_json(const std::string &filename, const std::vector<email_content> &emailData);

#endif // EMAIL_PROCESSING
