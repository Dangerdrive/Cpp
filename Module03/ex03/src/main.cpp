/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:32:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/23 14:30:01 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

int main() {
    // Create DiamondTrap objects
    DiamondTrap diamond1("Diamondy");
    DiamondTrap diamond2("Trapster");

    // Test attack function
    diamond1.attack("Trapster");
    diamond2.takeDamage(20);

    // Test repair function
    diamond2.beRepaired(10);

    // Test special capacity
    diamond1.whoAmI();

    // Test energy points and hit points
    diamond1.attack("Trapster");
    diamond1.attack("Trapster");
    diamond1.attack("Trapster"); // Should fail due to lack of energy points

    // Test taking damage
    diamond2.takeDamage(100); // Should reduce hit points to 0
    diamond2.beRepaired(5); // Should fail due to lack of hit points

    return 0;
}
