/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:32:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/23 12:32:37 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>

int main() {
    ScavTrap scav1("Scavvy");
    ScavTrap scav2("Trapster");

    scav1.attack("Trapster");
    scav2.takeDamage(20);

    scav2.beRepaired(10);

    scav1.guardGate();

    return 0;
}
