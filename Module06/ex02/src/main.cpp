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