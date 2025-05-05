/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:24:54 by fde-alen          #+#    #+#             */
/*   Updated: 2025/05/01 15:24:55 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

// Test function templates
template <typename T>
void printElement(T& element) {
    std::cout << element << " ";
}

void increment(int& num) {
    num += 1;
}

void capitalize(std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    // Test with int array
    int intArray[] = {1, 2, 3, 4, 5};
    size_t intLength = sizeof(intArray) / sizeof(intArray[0]);
    
    std::cout << "Original int array: ";
    iter(intArray, intLength, printElement<int>);
    std::cout << std::endl;
    
    iter(intArray, intLength, increment);
    std::cout << "After increment: ";
    iter(intArray, intLength, printElement<int>);
    std::cout << std::endl;
    
    // Test with string array
    std::string strArray[] = {"hello", "world", "template"};
    size_t strLength = sizeof(strArray) / sizeof(strArray[0]);
    
    std::cout << "\nOriginal string array: ";
    iter(strArray, strLength, printElement<std::string>);
    std::cout << std::endl;
    
    iter(strArray, strLength, capitalize);
    std::cout << "After capitalize: ";
    iter(strArray, strLength, printElement<std::string>);
    std::cout << std::endl;
    
    return 0;
}