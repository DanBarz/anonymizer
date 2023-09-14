
#include "validation.h"
#include "anonymizer.h"
#include "email_processing.h"
#include <vector>
#include <iostream>

// building functionality in steps


std::vector<anonymized_pattern> patterns;

int main() {

    initialize_patterns(patterns);
    validate_email_data(patterns);

    return 0;
}