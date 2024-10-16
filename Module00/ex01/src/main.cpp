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
/*◦ If the user enters this command, they are prompted to input the information
of the new contact one field at a time. Once all the fields have been completed,
add the contact to the phonebook.
◦ The contact fields are: first name, last name, nickname, phone number, and
darkest secret. A saved contact can’t have empty fields.*/
if (command.compare("ADD") == 0) {
	//TODO:get contact id available

	set_field(command, "First Name");
	set_field(command, "Last Name");
	set_field(command, "Nickname");
	set_field(command, "Phone Number");
	set_field(command, "Darkest Secret");


}
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
else if (command.compare("SEARCH") == 0) {
	//TODO
}
else if (command.compare("EXIT") == 0) {
	std::cout << "exiting PhoneBook..." << std::endl;
	return 0;
}
else
	std::cout << "Invalid command. Try a valid one: ADD, SEARCH or EXIT" << std::endl;

}
}