#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>
#include <iostream>

int main() {
    // Test with vector
    try {
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        
        std::vector<int>::iterator it = easyfind(vec, 2);
        std::cout << "Found value 2 at position " << std::distance(vec.begin(), it) << std::endl;
        
        easyfind(vec, 5); // This should throw
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Test with list
    try {
        std::list<int> lst;
        lst.push_back(10);
        lst.push_back(20);
        lst.push_back(30);
        
        std::list<int>::iterator it = easyfind(lst, 20);
        std::cout << "Found value 20 in list" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Test with deque
    try {
        std::deque<int> dq;
        dq.push_back(100);
        dq.push_back(200);
        dq.push_back(300);
        
        std::deque<int>::iterator it = easyfind(dq, 300);
        std::cout << "Found value 300 in deque" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}