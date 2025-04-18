/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/17 22:04:43 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include <iostream>

int main() {
    try {
        Bureaucrat boss("Zaphod", 1);
        Intern intern;

        // Test creating known forms
        AForm* shrubbery = intern.makeForm("shrubbery creation", "home");
        AForm* robotomy = intern.makeForm("robotomy request", "Marvin");
        AForm* pardon = intern.makeForm("presidential pardon", "Arthur");

        if (shrubbery) {
            boss.signForm(*shrubbery);
            boss.executeForm(*shrubbery);
            delete shrubbery;
        }

        if (robotomy) {
            boss.signForm(*robotomy);
            boss.executeForm(*robotomy);
            delete robotomy;
        }

        if (pardon) {
            boss.signForm(*pardon);
            boss.executeForm(*pardon);
            delete pardon;
        }

        // Test unknown form
        AForm* unknown = intern.makeForm("unknown form", "target");
        if (unknown) {
            delete unknown;
        }

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
