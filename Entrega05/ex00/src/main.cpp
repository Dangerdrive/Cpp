/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:36 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/25 17:18:07 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    try {
        // Test valid grade
        Bureaucrat b1("Alice", 2);
        std::cout << b1 << std::endl;

        // Test increment
        b1.incrementGrade();
        std::cout << "After increment: " << b1 << std::endl;

        // Test decrement
        b1.decrementGrade();
        std::cout << "After decrement: " << b1 << std::endl;

        // Test too high grade
        try {
            Bureaucrat b2("Bob", 0);
        } catch (std::exception& e) {
            std::cerr << "\nError creating Bob: " << e.what() << std::endl;
        }

        // Test too low grade
        try {
            Bureaucrat b3("Charlie", 151);
        } catch (std::exception& e) {
            std::cerr << "Error creating Charlie: " << e.what() << std::endl;
        }

        // Test increment too high
        try {
            Bureaucrat b4("Dave", 1);
            std::cout << b4 << std::endl;
            b4.incrementGrade();
        } catch (std::exception& e) {
            std::cerr << "Error incrementing Dave: " << e.what() << std::endl;
        }

        // Test decrement too low
        try {
            Bureaucrat b5("Eve", 150);
            std::cout << b5 << std::endl;
            b5.decrementGrade();
        } catch (std::exception& e) {
            std::cerr << "Error decrementing Eve: " << e.what() << std::endl;
        }

    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    // Bureaucrat b4("Dave", 1);
    // b4.incrementGrade();

    return 0;
}
