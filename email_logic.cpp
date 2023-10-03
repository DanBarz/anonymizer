#include "email_logic.h"
#include "gmail_connector.h"
#include <iostream>

void EmailLogic::processEmails(int num_emails) {
    std::string email_data = GmailConnector::fetchEmails(num_emails);
    std::cout << email_data << std::endl;
}
