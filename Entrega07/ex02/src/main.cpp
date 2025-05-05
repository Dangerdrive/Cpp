/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:13:03 by fde-alen          #+#    #+#             */
/*   Updated: 2025/05/01 19:19:44 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>

int main() {
    Array<int> empty;
    std::cout << "=======Test default constructor=======\nEmpty array size: " << empty.size() << std::endl;

    Array<int> numbers(5);
    std::cout << "\n=======Test constructor with size=====\nNumbers array size: " << numbers.size() << std::endl;

    for (unsigned int i = 0; i < numbers.size(); i++) {
        numbers[i] = i * 2;
    }

    std::cout << "Array elements: ";
    for (unsigned int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    Array<int> copy(numbers);
    std::cout << "\n=======Test copy constructor=======\nCopy array elements: ";
    for (unsigned int i = 0; i < copy.size(); i++) {
        std::cout << copy[i] << " ";
    }
    std::cout << std::endl;

    Array<int> assigned;
    assigned = numbers;
    std::cout << "\n=======Test copy constructor=======\nAssigned array elements: ";
    for (unsigned int i = 0; i < assigned.size(); i++) {
        std::cout << assigned[i] << " ";
    }
    std::cout << std::endl;

    try {
        std::cout << "\n====Test out of bounds exception====\nTrying to access index 10: ";
        std::cout << numbers[10] << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "!";

    std::cout << "\n=======Test with different type=======\nStrings array: ";
    for (unsigned int i = 0; i < strings.size(); i++) {
        std::cout << strings[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}