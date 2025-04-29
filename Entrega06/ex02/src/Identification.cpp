/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identification.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:20:14 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/29 20:14:08 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void) {
    std::srand(std::time(0));
    int random = std::rand() % 3;
    
    switch (random) {
        case 0: 
            std::cout << "Creating an A object..." << std::endl;
            return new A();
        case 1:
            std::cout << "Creating an B object..." << std::endl;
            return new B();
        case 2:
            std::cout << "Creating an C object..." << std::endl;
            return new C();
    }
    return NULL;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}
}