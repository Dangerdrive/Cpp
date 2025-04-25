/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/24 21:05:05 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "=====Creating valid bureaucrat=====" << std::endl;
        Bureaucrat highRank("Zaphod", 1);
        Bureaucrat midRank("Arthur", 50);
        Bureaucrat lowRank("Ford", 150);


        std::cout << "\n=====ShrubberyCreationForm tests=====" << std::endl;
        ShrubberyCreationForm shrubbery("home");
        std::cout << shrubbery << std::endl;

        lowRank.signForm(shrubbery);  
        lowRank.executeForm(shrubbery);

        midRank.signForm(shrubbery);
        midRank.executeForm(shrubbery);


        std::cout << "\n=====RobotomyRequestForm tests=====" << std::endl;
        RobotomyRequestForm robotomy("Marvin");
        std::cout << robotomy << std::endl;

        midRank.signForm(robotomy);
        midRank.executeForm(robotomy);

        highRank.executeForm(robotomy); // Should succeed (50% chance)

        std::cout << "\n=====PresidentialPardonForm tests=====" << std::endl;        
        PresidentialPardonForm pardon("Trillian");
        std::cout << pardon << std::endl;

        midRank.signForm(pardon);
        highRank.signForm(pardon); 
        highRank.executeForm(pardon);

        std::cout << "\n=====Try to execute unsigned form=====" << std::endl;        
        PresidentialPardonForm pardon2("Slartibartfast");
        highRank.executeForm(pardon2);

    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
