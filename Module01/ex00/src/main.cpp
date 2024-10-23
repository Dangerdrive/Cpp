#include <iostream>
#include "../includes/Zombie.hpp"

int main() {
    Zombie phonebook;
    Zombie new_contact;
    std::string command;

    std::cout << "Welcome to PhoneBook" << std::endl;

    while (1) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command); // Change to getline to capture entire line

        if (command.empty()) { // Check if the command is empty
            std::cout << "Error: No command entered. Please try again." << std::endl;
            continue; // Skip the rest of the loop and prompt again
        }

        if (command.compare("ADD") == 0) {
            new_contact.setField("First Name");
            new_contact.setField("Last Name");
            new_contact.setField("Nickname");
            new_contact.setField("Phone Number");
            new_contact.setField("Darkest Secret");
            phonebook.AddContact(new_contact);
        } else if (command.compare("SEARCH") == 0) {
            if (phonebook.getContactCount() == 0) {
                std::cout << "No contacts added. ADD a contact first." << std::endl;
            } else {
                phonebook.DisplaySearchContacts();
                phonebook.Search();
            }
        } else if (command.compare("EXIT") == 0) {
            std::cout << "Exiting PhoneBook..." << std::endl;
            return 0;
        } else {
            std::cout << "Invalid command. Try a valid one: ADD, SEARCH or EXIT" << std::endl;
        }
    }
}
