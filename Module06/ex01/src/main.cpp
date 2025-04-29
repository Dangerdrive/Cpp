#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    Data original;
    original.number = 42;
    original.text = "Hello, Serialization!";

    // Serialize
    uintptr_t raw = Serializer::serialize(&original);
    std::cout << "Serialized value: " << raw << std::endl;

    // Deserialize
    Data* restored = Serializer::deserialize(raw);
    
    // Verify
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