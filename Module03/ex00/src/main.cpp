/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/17 00:23:29 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int main() {
    // Create ClapTrap objects
    ClapTrap clap1("Clappy");
    ClapTrap clap2("Trappy");

    // Test attack function
    clap1.attack("Trappy");
    clap2.takeDamage(5);

    // Test repair function
    clap2.beRepaired(3);

    // Test energy points and hit points
    clap1.attack("Trappy");
    clap1.attack("Trappy");
    clap1.attack("Trappy"); // Should fail due to lack of energy points

    // Test taking damage
    clap2.takeDamage(10); // Should reduce hit points to 0
    clap2.beRepaired(5); // Should fail due to lack of hit points

    return 0;
}
