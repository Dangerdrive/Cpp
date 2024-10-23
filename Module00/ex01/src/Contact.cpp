#include <iostream>
#include "../includes/Contact.hpp"

Zombie::Zombie() {}
Zombie::~Zombie() {}

void Zombie::setFirstName(const std::string& entry) { this->name = entry; }
void Zombie::setLastName(const std::string& entry) { this->last_name = entry; }
void Zombie::setNickname(const std::string& entry) { this->nickname = entry; }
void Zombie::setPhoneNumber(const std::string& entry) { this->phonenumber = entry; }
void Zombie::setDarkestSecret(const std::string& entry) { this->darkest_secret = entry; }

void Zombie::setField(const std::string& field) {
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

std::string Zombie::getName() const { return this->name; }
std::string Zombie::getLastName() const { return this->last_name; }
std::string Zombie::getNickname() const { return this->nickname; }
std::string Zombie::getPhoneNumber() const { return this->phonenumber; }
std::string Zombie::getDarkestSecret() const { return this->darkest_secret; }