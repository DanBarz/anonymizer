#include "gui.h"
#include "splashkit.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>

// Function to display text on the GUI
void display_text(const std::string &text, int x, int y) {
    draw_text(text, COLOR_BLACK, "arial", 16, x, y);
}

void init_gui(GUI &gui, const std::string &configFile) {
    try {
        nlohmann::json jsonConfig;
        std::ifstream configFileStream(configFile);
        
        if (!configFileStream.is_open()) {
            std::cerr << "Error opening config file: " << configFile << std::endl;
            exit(1);
        }
        
        configFileStream >> jsonConfig;
        configFileStream.close();
        
        gui.title = jsonConfig["title"];
        gui.width = jsonConfig["width"];
        gui.height = jsonConfig["height"];
    } catch (const std::exception &e) {
        std::cerr << "Error reading JSON configuration: " << e.what() << std::endl;
        exit(1);
    }
}

void run_gui(GUI &gui) {
    open_window(gui.title, gui.width, gui.height);

    nlohmann::json jsonData;
    std::ifstream jsonFileStream("anonymized_data.json");

    if (!jsonFileStream.is_open()) {
        std::cerr << "Error opening JSON file: anonymized_data.json" << std::endl;
        exit(1);
    }

    jsonFileStream >> jsonData;
    jsonFileStream.close();

    int current_entry = 0;
    int total_entries = jsonData.size();

    bool space_pressed = false;
    bool window_closed = false;

    while (true) {
        
            process_events();

            if (window_close_requested(gui.title)) {
                break;  // Exit the loop if the user closes the window
            }

            if (current_entry < total_entries) {
                clear_screen(COLOR_WHITE);

                const auto &entry = jsonData[current_entry];
                std::string from = entry["from"];
                write_line("from: " + from);
                std::string to = entry["to"];
                write_line("to: " + to);
                std::string subject = entry["subject"];
                write_line("subject: " + subject);
                std::string content = entry["content"];
                write_line("content: " + content);

                display_text("From: " + from, 20, 20);
                display_text("To: " + to, 20, 40);
                display_text("Subject: " + subject, 20, 60);
                display_text("Content: " + content, 20, 80);

                refresh_screen(60);
                delay(2000);

                ++current_entry;
            
        }
    }

    close_window(gui.title);
}



// the close window is working on this
// void run_gui(GUI &gui) {
//     open_window(gui.title, gui.width, gui.height);

//     nlohmann::json jsonData;
//     std::ifstream jsonFileStream("anonymized_data.json");

//     if (!jsonFileStream.is_open()) {
//         std::cerr << "Error opening JSON file: anonymized_data.json" << std::endl;
//         exit(1);
//     }

//     jsonFileStream >> jsonData;
//     jsonFileStream.close();

//     int current_entry = 0;
//     int total_entries = jsonData.size();

//     bool space_pressed = false;
//     bool window_closed = false;

//     while (true) {
//         process_events();

//         if (window_close_requested(gui.title)) {
//             break;  // Exit the loop if the user closes the window
//         }

//         if (current_entry < total_entries) {
//             clear_screen(COLOR_WHITE);

//             const auto &entry = jsonData[current_entry];
//             std::string from = entry["from"];
//             std::string to = entry["to"];
//             std::string subject = entry["subject"];
//             std::string content = entry["content"];

//             display_text("From: " + from, 20, 20);
//             display_text("To: " + to, 20, 40);
//             display_text("Subject: " + subject, 20, 60);
//             display_text("Content: " + content, 20, 80);

//             refresh_screen(60);

//             ++current_entry;
//         }
//     }

//     close_window(gui.title);
// }

// this shows the text well but does not close
// void run_gui(GUI &gui) {
//     open_window(gui.title, gui.width, gui.height);

//     nlohmann::json jsonData;
//     std::ifstream jsonFileStream("anonymized_data.json");

//     if (!jsonFileStream.is_open()) {
//         std::cerr << "Error opening JSON file: anonymized_data.json" << std::endl;
//         exit(1);
//     }

//     jsonFileStream >> jsonData;
//     jsonFileStream.close();

//     int current_entry = 0;
//     int total_entries = jsonData.size();

//     bool space_pressed = false;
//     bool window_closed = false;

    
//     process_events();

//     if (!window_close_requested(gui.title) && current_entry < total_entries) {
//         clear_screen(COLOR_WHITE);

//         const auto &entry = jsonData[current_entry];
//         std::string from = entry["from"];
//         std::string to = entry["to"];
//         std::string subject = entry["subject"];
//         std::string content = entry["content"];

//         display_text("From: " + from, 20, 20);
//         display_text("To: " + to, 20, 40);
//         display_text("Subject: " + subject, 20, 60);
//         display_text("Content: " + content, 20, 80);

//         refresh_screen(60);

//         ++current_entry;

    
    

//     close_window(gui.title);
// }



// void run_gui(GUI &gui) {
//     open_window(gui.title, gui.width, gui.height);

//     do {
//         // Load and display text from anonymized_data.json
//     try {
//         nlohmann::json jsonData;
//         std::ifstream jsonFileStream("anonymized_data.json");

//         if (!jsonFileStream.is_open()) {
//             std::cerr << "Error opening JSON file: anonymized_data.json" << std::endl;
//             exit(1);
//         }

//         jsonFileStream >> jsonData;
//         jsonFileStream.close();

//         // Define starting position for displaying text
//         int x = 20;
//         int y = 20;

//         // Display each entry from the JSON file
//         for (const auto &entry : jsonData) {
//             std::string from = entry["from"];
//             std::string to = entry["to"];
//             std::string subject = entry["subject"];
//             std::string content = entry["content"];

//             // Display each field on the GUI
//             display_text("From: " + from, x, y);
//             y += 20; // Move down for the next field
//             display_text("To: " + to, x, y);
//             y += 30;
//             display_text("Subject: " + subject, x, y);
//             y += 20;
//             display_text("Content: " + content, x, y);
//             y += 40; // Leave extra space between entries
//         }
//     } catch (const std::exception &e) {
//         std::cerr << "Error reading JSON data: " << e.what() << std::endl;
//         exit(1);
//     }

//         refresh_screen(60); // Refresh the screen at 60 FPS

//     } while (!window_close_requested(gui.title));

//     close_window(gui.title);
// }