/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:47:26 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/15 22:13:43 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Harl.hpp"
#include <iostream>

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

void Harl::filterComplaints(std::string level) {

    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    int index = 0;
    while (index < 4 && levels[index] != level) {
        index++;
    }
    if (index >= 4) {
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
        return;
    }
    switch (index) {
        case 0:
            debug();
            index++;
        case 1:
            info();
            index++;
        case 2:
            warning();
            index++;
        case 3:
            error();
            break;
        default:
            break;
    }
}
