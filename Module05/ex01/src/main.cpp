/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/17 21:55:04 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
    try {
        // Test valid form creation
        Form f1("Tax Form", 50, 75);
        std::cout << f1 << std::endl;

        // Test invalid form creation
        try {
            Form f2("Invalid Form", 0, 151);
        } catch (std::exception& e) {
            std::cerr << "Error creating form: " << e.what() << std::endl;
        }

        // Test signing forms
        Bureaucrat b1("Alice", 30);
        Bureaucrat b2("Bob", 60);

        // Alice can sign (grade 30 <= 50)
        b1.signForm(f1);
        std::cout << f1 << std::endl;

        // Bob cannot sign (grade 60 > 50)
        b2.signForm(f1);

        // Test already signed form
        Form f3("Application", 40, 50);
        b1.signForm(f3);
        b2.signForm(f3); // Bob can't sign but message shows it's already signed

    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
