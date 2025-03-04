#include <iostream>
#include "../includes/Zombie.hpp"

int main() {

    int numberOfZombies = 10;

    Zombie* horde = zombieHorde(numberOfZombies, "Oli Zombie");

    for (int i = 0; i < numberOfZombies; i++) {
        horde[i].announce();
    }

delete[] horde;
}
