#include <iostream>
#include "../includes/Zombie.hpp"

Phonebook* newZombie( std::string name ) {
    Phonebook* new_zombie = new Phonebook(name);
    return new_zombie;
}
