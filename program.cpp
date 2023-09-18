
#include "validation.h"
#include "revert.h"
#include "gui.h"
#include "anonymizer.h"
#include "email_processing.h"
#include <vector>
#include <iostream>

// This is the menu that will be displayed to the user
void menu(placeholder_data& placeholders ) {

    int choice;

    // Menu for user to choose if they want to process the CSV file now
    std::cout << "Do you want to process your CSV to insert back the secure information?" << std::endl;
    std::cout << "Press 1 for yes and 2 for no: ";
    std::cin >> choice;

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