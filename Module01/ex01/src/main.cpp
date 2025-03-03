#include <iostream>
#include "../includes/Zombie.hpp"

int main() {

Zombie* zombieCat = newZombie("Oli Zombie");
zombieCat->announce();

randomChump("Gin Zombie");

delete zombieCat;
}
