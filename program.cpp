
#include "email_logic.h"
#include "gmail_connector.h"
#include "validation.h"
#include "revert.h"
#include "gui.h"
#include "anonymizer.h"
#include "email_processing.h"
#include <vector>
#include <iostream>
#include "splashkit.h"

// Data Anonymizer V 1.0
// This program is designed to anonymize data contained in a JSON file (output data received from gmail perhaps)
// The program will read the JSON file and anonymize the data, then output the data to a new JSON file
// The program has a GUI that will appear after the data has been anonymized to allow the user to verify the data

// The user will then use that anonymous JSON data in something like chatGPT and then output the data to a CSV file

// The program will also allow the user to revert the anonymized data back to the original data
// It takes the information recieved in the form of a CSV file and processes it to insert back the secure information
// From this point you can insert it into a database or whatever you want to do with it

// This is the menu that will be displayed to the user
void menu(placeholder_data& placeholders ) {

    int choice;

    // Menu for user to choose if they want to process the CSV file now
    write_line ("Do you want to process your CSV to insert back the secure information?");
    write_line ("Press 1 for yes and 2 for no: ");
    choice = convert_to_integer(read_line());
    

    // Working with .csv file
    if (choice == 1) {

        // Load the mappings from the JSON file
        loadMappingsFromJson(placeholders);

        // Process the CSV data and write to a new CSV file
        processCSVWithMapping("finished_data.csv", "output_data.csv", placeholders.mappings);
    }
}

// Main function starts
int main() {
    
    // Create a placeholder_data object to store the mappings
    placeholder_data placeholders;

    // Load the resources
    load_resources();

    // Initialize the patterns used for anonymization
    initialize_patterns();

    EmailLogic::processEmails(5);

    // This outputs the data to the console and processes the data
    validate_email_data(placeholders);
    
    // variable for GUI
    GUI myGui;

    // Initialize the GUI
    init_gui(myGui, "gui_config.json");

    // Menu for user to choose if they want to process the CSV file now
    menu(placeholders);

    // Run the GUI to display the anon data from the JSON file for verification
    run_gui(myGui);

    // program finished message
    cout << "Program finished." << endl;    
    return 0;
}