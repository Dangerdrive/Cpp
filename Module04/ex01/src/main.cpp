/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/11 19:59:53 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

void run_wrong_animal_tests() {
    std::cout << "\n----- Wrong Animal Tests with Brain -----" << std::endl;
    
    const WrongAnimal* wrongCat = new WrongCat();
    
    std::cout << wrongCat->getType() << std::endl;
   
    delete wrongCat;  // Only calls WrongAnimal's destructor!
    
    std::cout << "--- Check for memory leaks! ---" << std::endl;
}

int main() {
    // Test basic functionality
    {
        std::cout << "----- Basic Test -----" << std::endl;
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;

        i->makeSound();
        j->makeSound();

        delete j;
        delete i;
    }

    // Test array of animals
    {
        std::cout << "\n----- Array Test -----" << std::endl;
        const int numAnimals = 4;
        Animal* animals[numAnimals];

        for (int i = 0; i < numAnimals/2; i++) {
            animals[i] = new Dog();
        }
        for (int i = numAnimals/2; i < numAnimals; i++) {
            animals[i] = new Cat();
        }

        for (int i = 0; i < numAnimals; i++) {
            animals[i]->makeSound();
            delete animals[i];
        }
    }

    // Test deep copy
    {
        std::cout << "\n----- Deep Copy Test -----" << std::endl;
        Dog original;
        original.getBrain()->setIdea(0, "I want to play!");

        Dog copy(original);
        std::cout << "Original's first idea: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy's first idea: " << copy.getBrain()->getIdea(0) << std::endl;

        // Modify the copy's brain
        copy.getBrain()->setIdea(0, "I want to sleep!");
        std::cout << "After modification:" << std::endl;
        std::cout << "Original's first idea: " << original.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copy's first idea: " << copy.getBrain()->getIdea(0) << std::endl;
    }

    //uncomment line below to show wrong/leaky behaviour
    //run_wrong_animal_tests();

    return 0;
}
