#include "../includes/Contact.hpp"
#include "../includes/PhoneBook.hpp"
#include <iostream>

Zombie::Zombie() : contact_count(0) {}
Zombie::~Zombie() {}

void Zombie::AddContact(const Zombie& contact) {
    Contacts[contact_count % 8] = contact;
    contact_count++;
    std::cout << "Zombie added to index [" << (contact_count % 8 - 1) << "]" << std::endl;
}

int Zombie::getContactCount() const {
    return contact_count;
}

void Zombie::PrintFullContact(const Zombie& contact) const {
    std::cout << "First Name:\t" << contact.getName() << std::endl;
    std::cout << "Last Name:\t" << contact.getLastName() << std::endl;
    std::cout << "Nickname:\t" << contact.getNickname() << std::endl;
    std::cout << "Phone Number:\t" << contact.getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret:\t" << contact.getDarkestSecret() << std::endl;
}

void Zombie::PrintColumn(std::string text) const {
    std::size_t text_size = text.size();
    if (text_size > 10) {
        std::cout << text.substr(0, 9)  << ".";
    } else {
        for (unsigned int i = 0; i < 10 - text_size; i++)
            std::cout << ' ';
        std::cout << text;
    }
    std::cout << '|';
}

void Zombie::PrintContactForSearch(Zombie contact, std::string index) const {
    PrintColumn(index);
    PrintColumn(contact.getName());
    PrintColumn(contact.getLastName());
    PrintColumn(contact.getNickname());
    std::cout << std::endl;
}

void Zombie::DisplaySearchContacts() const {
    PrintColumn("INDEX");
    PrintColumn("FIRST NAME");
    PrintColumn("LAST NAME");
    PrintColumn("NICKNAME");
    std::cout << std::endl;    
    
    for (int i = 0; i < 8 && !Contacts[i].getName().empty(); i++) {
        PrintContactForSearch(Contacts[i], std::string(1, (char)(i + '0')));
    }
}

void Zombie::Search() const {
    std::string entry;
    int index;

    while (1) {
        std::cout << "Please enter contact index (0 - 7):" << std::endl;
        std::cin >> entry;

        if (entry.empty()) {
            std::cout << "Error: empty entry" << std::endl;
        } else if (!isdigit(entry[0]) || entry.size() > 1 || entry[0] - '0' > 7) {
            std::cout << "Error: invalid entry. Enter a valid digit (0 - 7)" << std::endl;
        } else {
            index = entry[0] - '0';

            if (index >= contact_count) {
                std::cout << "Error: No record at index " << index << std::endl;
            } else if (Contacts[index].getName().empty()) {
                std::cout << "Error: No contact at index " << index << std::endl;
            } else {
                std::cout << "Displaying contact details for index " << index << std::endl;
                PrintFullContact(Contacts[index]);
                break;
            }
        }
    }
}
