#ifndef GUI_H
#define GUI_H
#include "anonymizer.h"
#include "json.hpp"
#include <string>

struct GUI {
    std::string title;
    int width;
    int height;
};

void load_resources();
void init_gui(GUI &gui, const std::string &configFile);
void run_gui(GUI &gui);

#endif // GUI_H
