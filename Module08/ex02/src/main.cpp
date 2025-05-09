/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:54:40 by fde-alen          #+#    #+#             */
/*   Updated: 2025/05/08 22:54:41 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() {
    // Test with MutantStack
    {
        MutantStack<int> mstack;
        mstack.push(5);
        mstack.push(17);
        std::cout << "Top: " << mstack.top() << std::endl;
        mstack.pop();
        std::cout << "Size: " << mstack.size() << std::endl;
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);
        
        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();
        ++it;
        --it;
        std::cout << "Elements: ";
        while (it != ite) {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;
    }

    // Compare with std::list
    {
        std::list<int> lst;
        lst.push_back(5);
        lst.push_back(17);
        std::cout << "Top: " << lst.back() << std::endl;
        lst.pop_back();
        std::cout << "Size: " << lst.size() << std::endl;
        lst.push_back(3);
        lst.push_back(5);
        lst.push_back(737);
        lst.push_back(0);
        
        std::list<int>::iterator it = lst.begin();
        std::list<int>::iterator ite = lst.end();
        ++it;
        --it;
        std::cout << "Elements: ";
        while (it != ite) {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;
    }

    return 0;
}