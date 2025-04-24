/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/23 18:07:50 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "Test create valid form" << std::endl;
        Form f1("Tax Form", 50, 75);
        std::cout << f1 << std::endl;

        std::cout << "\nTest invalid form creation" << std::endl;
        try {
            Form f2("Invalid Form", 0, 151);
        } catch (std::exception& e) {
            std::cerr << "Error creating form: " << e.what() << std::endl;
        }

        std::cout << "\nTests signing forms" << std::endl;
        Bureaucrat b1("Alice", 30);
        Bureaucrat b2("Bob", 60);

        std::cout << "\nTest - Alice can sign (grade 30 <= 50)" << std::endl;
        b1.signForm(f1);
        std::cout << f1 << std::endl;

        std::cout << "\nTest - Bob cannot sign (grade 60 > 50)" << std::endl;
        b2.signForm(f1);

        std::cout << "\nTest already signed form" << std::endl;
        Form f3("Application", 40, 50);
        b1.signForm(f3);
        b1.signForm(f3);
        b2.signForm(f3);

    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
