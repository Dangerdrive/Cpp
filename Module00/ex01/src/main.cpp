#include <iostream>
#include "../includes/Contact.class.hpp"
#include "../includes/PhoneBook.class.hpp"

void set_field(std::string &entry, const std::string &field) {
    while (1) {
        std::cout << "Please enter " << field << ":" << std::endl;
        std::cin >> entry;		
        if (!entry.empty()) {
            // set the value in the correct field
            break;
        } else {
            std::cout << "Error: empty entry" << std::endl;
        }
    }
}


int main() {
    Phonebook phonebook;  // Create a PhoneBook instance
    Contact new_contact;
    std::string command;

    std::cout << "Welcome to PhoneBook" << std::endl;

    while(1) {
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command.compare("ADD") == 0) {
            // Get the contact details by prompting the user
            new_contact.setField("First Name");
            new_contact.setField("Last Name");
            new_contact.setField("Nickname");
            new_contact.setField("Phone Number");
            new_contact.setField("Darkest Secret");

            // Now that new_contact is filled, add it to the phonebook
            phonebook.AddContact(new_contact);

/*• SEARCH: display a specific contact
◦ Display the saved contacts as a list of 4 columns: index, first name, last
name and nickname.
◦ Each column must be 10 characters wide. A pipe character (’|’) separates
them. The text must be right-aligned. If the text is longer than the column,
it must be truncated and the last displayable character must be replaced by a
dot (’.’).
◦ Then, prompt the user again for the index of the entry to display. If the index
is out of range or wrong, define a relevant behavior. Otherwise, display the
contact information, one field per line.*/
        } else if (command.compare("SEARCH") == 0) {
            // TODO: Implement search functionality
        } else if (command.compare("EXIT") == 0) {
            std::cout << "Exiting PhoneBook..." << std::endl;
            return 0;
        } else {
            std::cout << "Invalid command. Try a valid one: ADD, SEARCH or EXIT" << std::endl;
        }
    }
}
