/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:19:17 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/29 20:25:18 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    Data original;
    original.number = 42;
    original.text = "Hello, Serialization!";

    std::cout << "Original data: " << original.number 
    << ", " << original.text << std::endl;
    
    uintptr_t raw = Serializer::serialize(&original);
    std::cout << "Serialized value: " << raw << std::endl;

    Data* restored = Serializer::deserialize(raw);
    
    std::cout << "Original address: " << &original << std::endl;
    std::cout << "Restored address: " << restored << std::endl;
    
    if (restored == &original) {
        std::cout << "\033[32mSuccess! Pointers match.\033[0m" << std::endl;
        std::cout << "Restored data: " << restored->number 
                  << ", " << restored->text << std::endl;
    } else {
        std::cout << "\033[31mError! Pointers don't match.\033[0m" << std::endl;
    }

    return 0;
}