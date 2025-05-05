#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    // Basic test
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest span: " << sp.longestSpan() << std::endl;

    // Test with range of iterators
    std::vector<int> bigVec;
    srand(time(0));
    for (int i = 0; i < 10000; ++i)
        bigVec.push_back(rand() % 1000000);
    
    Span bigSpan(10000);
    bigSpan.addRange(bigVec.begin(), bigVec.end());
    std::cout << "Big span shortest: " << bigSpan.shortestSpan() << std::endl;
    std::cout << "Big span longest: " << bigSpan.longestSpan() << std::endl;

    // Exception tests
    try {
        Span small(1);
        small.addNumber(42);
        small.addNumber(43); // Should throw
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        Span empty(10);
        empty.shortestSpan(); // Should throw
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}