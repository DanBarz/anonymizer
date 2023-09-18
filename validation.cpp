
#include "validation.h"
#include "splashkit.h"
#include "email_processing.h"
#include "anonymizer.h"
#include <vector>
#include <iostream>

// This outputs the data to the console and processes the data
void validate_email_data(placeholder_data placeholders) {
    vector<email_content> emailData = read_data_from_json("data.json");

    // Continue with anonymization and other operations
    for (email_content &email : emailData) {

        // Display the original email content
        cout << "Original Content (From): " << email.from << endl;
        cout << "Original Content (To): " << email.to << endl;
        cout << "Original Content (Subject): " << email.subject << endl;
        cout << "Original Content (Content): " << email.content << endl;

        // Anonymize all fields using the initialized patterns
        email.from = anonymize_text(email.from, placeholders);
        email.to = anonymize_text(email.to, placeholders);
        email.subject = anonymize_text(email.subject, placeholders);
        email.content = anonymize_text(email.content, placeholders);

        // Display the anonymized email content
        cout << "Anonymized Content (From): " << email.from << endl;
        cout << "Anonymized Content (To): " << email.to << endl;
        cout << "Anonymized Content (Subject): " << email.subject << endl;
        cout << "Anonymized Content (Content): " << email.content << endl;

    }

    // Save the data to a JSON file
    save_data_to_json("anonymized_data.json", emailData);
}
