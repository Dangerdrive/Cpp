#include <iostream>
#include "../includes/Zombie.hpp"

Contact::Contact() {}
Contact::Contact(std::string name) : name(name) {}
Contact::~Contact() {
    std::cout << name << std::endl
}

void Contact::announce() {
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl
}

std::string Contact::getName() const { return this->name; }