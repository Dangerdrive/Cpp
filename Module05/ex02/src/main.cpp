/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/17 21:57:53 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
    try {
        Bureaucrat highRank("Zaphod", 1);
        Bureaucrat midRank("Arthur", 50);
        Bureaucrat lowRank("Ford", 150);

        // ShrubberyCreationForm tests
        ShrubberyCreationForm shrubbery("home");
        std::cout << shrubbery << std::endl;

        lowRank.signForm(shrubbery);  // Should succeed (145 needed)
        lowRank.executeForm(shrubbery); // Should fail (137 needed)

        midRank.executeForm(shrubbery); // Should succeed

        // RobotomyRequestForm tests
        RobotomyRequestForm robotomy("Marvin");
        std::cout << robotomy << std::endl;

        midRank.signForm(robotomy); // Should succeed (72 needed)
        midRank.executeForm(robotomy); // Should fail (45 needed)

        highRank.executeForm(robotomy); // Should succeed (50% chance)

        // PresidentialPardonForm tests
        PresidentialPardonForm pardon("Trillian");
        std::cout << pardon << std::endl;

        midRank.signForm(pardon); // Should fail (25 needed)
        highRank.signForm(pardon); // Should succeed
        highRank.executeForm(pardon); // Should succeed

        // Try to execute unsigned form
        PresidentialPardonForm pardon2("Slartibartfast");
        highRank.executeForm(pardon2); // Should fail (not signed)

    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
