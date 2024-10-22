#include <iostream>
#include "../includes/Contact.hpp"

Contact::Contact() {}
Contact::~Contact() {}

void Contact::setFirstName(const std::string& entry) { this->first_name = entry; }
void Contact::setLastName(const std::string& entry) { this->last_name = entry; }
void Contact::setNickname(const std::string& entry) { this->nickname = entry; }
void Contact::setPhoneNumber(const std::string& entry) { this->phonenumber = entry; }
void Contact::setDarkestSecret(const std::string& entry) { this->darkest_secret = entry; }

void Contact::setField(const std::string& field) {
    std::string entry;

    while (1) {
        std::cout << "Please enter " << field << ":" << std::endl;
        std::getline(std::cin, entry); // Use getline to read the entire line

        if (entry.empty()) {
            std::cout << "Error: empty entry" << std::endl; // Error for empty input
            std::cout << "Please enter " << field << ":" << std::endl;
        } else {
            if (field == "First Name") {
                setFirstName(entry);
            } else if (field == "Last Name") {
                setLastName(entry);
            } else if (field == "Nickname") {
                setNickname(entry);
            } else if (field == "Phone Number") {
                setPhoneNumber(entry);
            } else if (field == "Darkest Secret") {
                setDarkestSecret(entry);
            }
            break; // Exit the loop if valid input is provided
        }
    }
}

std::string Contact::getFirstName() const { return this->first_name; }
std::string Contact::getLastName() const { return this->last_name; }
std::string Contact::getNickname() const { return this->nickname; }
std::string Contact::getPhoneNumber() const { return this->phonenumber; }
std::string Contact::getDarkestSecret() const { return this->darkest_secret; }