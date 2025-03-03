#include <iostream>
#include "../includes/Zombie.hpp"

Zombie::Zombie() : name("Unnamed") {}

Zombie::Zombie(std::string name) : name(name) {}

void Zombie::announce() {
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

std::string Zombie::getName() const { return this->name; }

Zombie::~Zombie(){
std::cout << name << " was exterminated. Shoting in the head really works" << std::endl;
}