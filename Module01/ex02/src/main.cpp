#include <iostream>
#include <string>

int main() {
    // A string variable initialized to "HI THIS IS BRAIN"
    std::string str = "HI THIS IS BRAIN";

    // A pointer to the string
    std::string* stringPTR = &str;

    // A reference to the string
    std::string& stringREF = str;

    // Print memory addresses
    std::cout << "Memory address of the string variable: " << &str << std::endl;
    std::cout << "Memory address held by stringPTR:      " << stringPTR << std::endl;
    std::cout << "Memory address held by stringREF:      " << &stringREF << std::endl;

    // Print values
    std::cout << "Value of the string variable:  " << str << std::endl;
    std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
    std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;

    return 0;
}
