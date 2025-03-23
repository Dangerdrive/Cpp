/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:31 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/23 11:57:55 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap() : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap " << _name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) {
    std::cout << "ClapTrap Copy constructor called" << std::endl;
    *this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    std::cout << "ClapTrap Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << _name << " destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
    if (_hitPoints == 0 || _energyPoints == 0) {
        std::cout << "ClapTrap " << _name << " can't attack. No hit points or energy points left!" << std::endl;
        return;
    }
    _energyPoints--;
    std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

// Take damage function
void ClapTrap::takeDamage(unsigned int amount) {
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " is already out of hit points!" << std::endl;
        return;
    }
    if (amount >= _hitPoints) {
        _hitPoints = 0;
    } else {
        _hitPoints -= amount;
    }
    std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage! It now has " << _hitPoints << " hit points." << std::endl;
}

// Be repaired function
void ClapTrap::beRepaired(unsigned int amount) {
    if (_hitPoints == 0 || _energyPoints == 0) {
        std::cout << "ClapTrap " << _name << " can't be repaired. No hit points or energy points left!" << std::endl;
        return;
    }
    _energyPoints--; // Repair costs 1 energy point
    _hitPoints += amount;
    std::cout << "ClapTrap " << _name << " is repaired for " << amount << " hit points! It now has " << _hitPoints << " hit points." << std::endl;
}
