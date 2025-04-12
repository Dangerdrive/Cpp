/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/11 20:10:21 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main() {
    // 1. Verify abstract class cannot be instantiated (uncomment for error)
    //AAnimal abstract; // Should cause compilation error
    
    // 2. Polymorphic behavior test
    {
        std::cout << "\n----- Polymorphic behavior test -----" << std::endl;

        const AAnimal* dog = new Dog();
        const AAnimal* cat = new Cat();
        
        dog->makeSound(); // Should bark
        cat->makeSound(); // Should meow
        
        delete dog;
        delete cat;
    }
    
    // 3. Array test (heterogeneous collection)
    {
        std::cout << "\n----- Array test -----" << std::endl;
        AAnimal* zoo[4];
        for (int i = 0; i < 2; i++) {
            zoo[i] = new Dog();
            zoo[i+2] = new Cat();
        }
        
        for (int i = 0; i < 4; i++) {
            zoo[i]->makeSound();
            delete zoo[i];
        }
    }
    
    // 4. Deep copy test
    {
        std::cout << "\n----- Deep copy test -----" << std::endl;
        Dog dog1;
        dog1.getBrain()->setIdea(0, "Original thought");
        
        Dog dog2(dog1);
        dog2.getBrain()->setIdea(0, "Modified thought");
        
        // Verify independent brains
        std::cout << dog1.getBrain()->getIdea(0) << " vs " 
                  << dog2.getBrain()->getIdea(0) << std::endl;
    }
    
    // 5. Assignment test
    {
        std::cout << "\n----- Assignment test -----" << std::endl;
        Cat cat1;
        Cat cat2;
        cat1.getBrain()->setIdea(0, "First idea");
        
        cat2 = cat1;
        cat2.getBrain()->setIdea(0, "Changed idea");
        
        // Verify independent brains after assignment
        std::cout << cat1.getBrain()->getIdea(0) << " vs " 
                  << cat2.getBrain()->getIdea(0) << std::endl;
    }
    
    return 0;
}