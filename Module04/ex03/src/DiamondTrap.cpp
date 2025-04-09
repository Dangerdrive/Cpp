/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:31 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/23 14:26:33 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

// Default constructor
DiamondTrap::DiamondTrap() : ClapTrap("Default DiamondTrap_clap_name"), FragTrap(), ScavTrap() {
    _name = "Default DiamondTrap";
    _hitPoints = FragTrap::_hitPoints; // Use FragTrap's hit points
    _energyPoints = ScavTrap::_energyPoints; // Use ScavTrap's energy points
    _attackDamage = FragTrap::_attackDamage; // Use FragTrap's attack damage
    std::cout << "DiamondTrap Default constructor called" << std::endl;
}

// Parameterized constructor
DiamondTrap::DiamondTrap(const std::string& name) : ClapTrap(name + "_clap_name"), FragTrap(), ScavTrap() {
    _name = name;
    _hitPoints = FragTrap::_hitPoints; // Use FragTrap's hit points
    _energyPoints = ScavTrap::_energyPoints; // Use ScavTrap's energy points
    _attackDamage = FragTrap::_attackDamage; // Use FragTrap's attack damage
    std::cout << "DiamondTrap " << _name << " constructor called" << std::endl;
}

// Copy constructor
DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), FragTrap(other), ScavTrap(other) {
    _name = other._name;
    std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    std::cout << "DiamondTrap Copy assignment operator called" << std::endl;
    if (this != &other) {
        ClapTrap::operator=(other);
        FragTrap::operator=(other);
        ScavTrap::operator=(other);
        _name = other._name;
    }
    return *this;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap " << _name << " destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target); // Use ScavTrap's attack function
}

// Special capacity
void DiamondTrap::whoAmI() {
    std::cout << "DiamondTrap name: " << _name << ", ClapTrap name: " << ClapTrap::_name << std::endl;
}
