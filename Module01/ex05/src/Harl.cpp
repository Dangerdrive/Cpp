/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:44:48 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/15 21:44:49 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Harl.hpp"
#include <iostream>

// Constructor: Initialize function pointers and level names
Harl::Harl() {
    complaintFunctions[0] = &Harl::debug;
    complaintFunctions[1] = &Harl::info;
    complaintFunctions[2] = &Harl::warning;
    complaintFunctions[3] = &Harl::error;

    levels[0] = "DEBUG";
    levels[1] = "INFO";
    levels[2] = "WARNING";
    levels[3] = "ERROR";
}

void Harl::debug() {
    std::cout << "[ DEBUG ]\n"
              << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!\n"
              << std::endl;
}

void Harl::info() {
    std::cout << "[ INFO ]\n"
              << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!\n"
              << std::endl;
}

void Harl::warning() {
    std::cout << "[ WARNING ]\n"
              << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.\n"
              << std::endl;
}

void Harl::error() {
    std::cout << "[ ERROR ]\n"
              << "This is unacceptable! I want to speak to the manager now.\n"
              << std::endl;
}

void Harl::complain(std::string level) {
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*complaintFunctions[i])();
            return;
        }
    }
    std::cout << "[ INVALID LEVEL ]\n"
              << "Harl doesn't know how to complain about this level.\n"
              << std::endl;
}
