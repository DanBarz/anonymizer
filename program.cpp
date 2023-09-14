
#include "validation.h"
#include "anonymizer.h"
#include "email_processing.h"
#include <vector>
#include <iostream>

int main() {

    placeholder_data placeholders;
    initialize_patterns();
    validate_email_data(placeholders);

    return 0;
}