#include "../includes/Harl.hpp"
#include <iostream>

int main() {
    Harl harl;

    std::cout << "Testing Harl's complaints:\n" << std::endl;

    // Test all levels
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");

    // Test an unknown level
    harl.complain("UNKNOWN");

    return 0;
}