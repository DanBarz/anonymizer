#include "gui.h"
#include "anonymizer.h"
#include "splashkit.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function to display text on the GUI
void load_resources() {

    load_font("arial", "DMSans_36pt-Bold.ttf");
}

void display_text(const std::string &text, int x, int y) {
    color text_color = random_color();
    draw_text(text, text_color, "arial", 16, x, y);
}

// Function to render a long string, splitting it into segments if necessary
void render_long_string(const std::string &text, int x, int y, int max_width, int font_size) {
    const std::string font_name = "arial";
    
    // Split the input string into segments of at most 111 characters each
    std::vector<std::string> segments;
    for (size_t i = 0; i < text.length(); i += 111) {
        segments.push_back(text.substr(i, 111));
    }

    // Render each segment on a new line
    for (const std::string &segment : segments) {
        draw_text(segment, COLOR_BLACK, font_name, font_size, x, y);
        y += text_height(segment, font_name, font_size);
    }
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

    while (true) {
        process_events();

        if (window_close_requested(gui.title)) {
            break;  // Exit the loop if the user closes the window
        }

        if (current_entry < total_entries) {
            clear_screen(COLOR_WHITE);

            const auto &entry = jsonData[current_entry];
            std::string from = entry["from"];
            std::string to = entry["to"];
            std::string subject = entry["subject"];
            std::string content = entry["content"];

            // Adjust the maximum width based on your window size (e.g., 1000 for a 1200x1000 window)
            render_long_string("From: " + from, 20, 20, 1000, 16);
            render_long_string("To: " + to, 20, 40, 1000, 16);
            render_long_string("Subject: " + subject, 20, 60, 1000, 16);
            render_long_string("Content: " + content, 20, 80, 1000, 16);

            refresh_screen(60);
            delay(2000);

            ++current_entry;
        }
        
    }
    
    close_window(gui.title);
}

