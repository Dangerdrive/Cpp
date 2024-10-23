#include <iostream>
#include "../includes/Zombie.hpp"

Zombie::Zombie() {}
Zombie::Zombie(std::string name) : name(name) {}
Zombie::~Zombie() {
    std::cout << name << std::endl
}

void Zombie::announce() {
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl
}

std::string Zombie::getName() const { return this->name; }