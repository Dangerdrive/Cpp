/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/25 17:02:35 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "\n=====Creating bureaucrat & intern=====" << std::endl;
        Bureaucrat boss("Zaphod", 1);
        Intern intern;

        std::cout << boss << std::endl;
        std::cout << "intern is here too\n" << std::endl;

        std::cout << "\n=====Test creating valid forms=====" << std::endl;
        AForm* shrubbery = intern.makeForm("shrubbery creation", "home");
        AForm* robotomy = intern.makeForm("robotomy request", "Marvin");
        AForm* pardon = intern.makeForm("presidential pardon", "Arthur");

        std::cout << "\n=====Test sign & exec forms=====" << std::endl;
        if (shrubbery) {
            boss.signForm(*shrubbery);
            boss.executeForm(*shrubbery);
            delete shrubbery;
            std::cout << std::endl;
        }

        if (robotomy) {
            boss.signForm(*robotomy);
            boss.executeForm(*robotomy);
            delete robotomy;
            std::cout << std::endl;
        }

        if (pardon) {
            boss.signForm(*pardon);
            boss.executeForm(*pardon);
            delete pardon;
        }

        std::cout << "\n=====Test creating unknown form=====" << std::endl;
        AForm* unknown = intern.makeForm("unknown form", "target");
        if (unknown) {
            delete unknown;
        }

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
