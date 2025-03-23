/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:31 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/23 13:25:19 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

// Default constructor
FragTrap::FragTrap() : ClapTrap("Default FragTrap") {
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap Default constructor called" << std::endl;
}

// Parameterized constructor
FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap " << _name << " constructor called" << std::endl;
}

// Copy constructor
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    std::cout << "FragTrap Copy constructor called" << std::endl;
}

// Copy assignment operator
FragTrap& FragTrap::operator=(const FragTrap& other) {
    std::cout << "FragTrap Copy assignment operator called" << std::endl;
    if (this != &other) { // Check for self-assignment
        ClapTrap::operator=(other); // Call base class assignment operator
    }
    return *this;
}

// Destructor
FragTrap::~FragTrap() {
    std::cout << "FragTrap " << _name << " destructor called" << std::endl;
}

// Override attack function
void FragTrap::attack(const std::string& target) {
    if (_hitPoints == 0 || _energyPoints == 0) {
        std::cout << "FragTrap " << _name << " can't attack. No hit points or energy points left!" << std::endl;
        return;
    }
    _energyPoints--; // Attack costs 1 energy point
    std::cout << "FragTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

// Special capacity
void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << _name << " requests a positive high five!" << std::endl;
}
