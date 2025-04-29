/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:18:40 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/29 18:18:41 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Identification.hpp"

int main() {
    // Test random generation
    Base* obj = generate();
    
    // Test pointer identification
    std::cout << "Pointer type: ";
    identify(obj);
    
    // Test reference identification
    std::cout << "Reference type: ";
    identify(*obj);
    
    delete obj;
    return 0;
}