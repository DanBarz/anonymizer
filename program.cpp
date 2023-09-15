
#include "validation.h"
#include "gui.h"
#include "anonymizer.h"
#include "email_processing.h"
#include <vector>
#include <iostream>

int main() {

    placeholder_data placeholders;
    initialize_patterns();
    validate_email_data(placeholders);

    
    GUI myGui;
    init_gui(myGui, "gui_config.json");
    run_gui(myGui);

    return 0;
}