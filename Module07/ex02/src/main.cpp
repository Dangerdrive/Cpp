#include "Array.hpp"
#include <iostream>

int main() {
    // Test default constructor
    Array<int> empty;
    std::cout << "Empty array size: " << empty.size() << std::endl;

    // Test constructor with size
    Array<int> numbers(5);
    std::cout << "Numbers array size: " << numbers.size() << std::endl;

    // Test element access and modification
    for (unsigned int i = 0; i < numbers.size(); i++) {
        numbers[i] = i * 2;
    }

    std::cout << "Numbers array elements: ";
    for (unsigned int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    // Test copy constructor
    Array<int> copy(numbers);
    std::cout << "Copy array elements: ";
    for (unsigned int i = 0; i < copy.size(); i++) {
        std::cout << copy[i] << " ";
    }
    std::cout << std::endl;

    // Test assignment operator
    Array<int> assigned;
    assigned = numbers;
    std::cout << "Assigned array elements: ";
    for (unsigned int i = 0; i < assigned.size(); i++) {
        std::cout << assigned[i] << " ";
    }
    std::cout << std::endl;

    // Test out of bounds exception
    try {
        std::cout << "Trying to access index 10: ";
        std::cout << numbers[10] << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Test with different type
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "!";

    std::cout << "Strings array: ";
    for (unsigned int i = 0; i < strings.size(); i++) {
        std::cout << strings[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}