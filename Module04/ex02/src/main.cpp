/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:32:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/23 14:14:05 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

int main() {
    // Create FragTrap objects
    FragTrap frag1("Fraggy");
    FragTrap frag2("Trapster");

    // Test attack function
    frag1.attack("Trapster");
    frag2.takeDamage(30);

    // Test repair function
    frag2.beRepaired(20);

    // Test special capacity
    frag1.highFivesGuys();

    // Test energy points and hit points
    frag1.attack("Trapster");
    frag1.attack("Trapster");
    frag1.attack("Trapster"); // Should fail due to lack of energy points

    // Test taking damage
    frag2.takeDamage(100); // Should reduce hit points to 0
    frag2.beRepaired(5); // Should fail due to lack of hit points

    return 0;
}
