#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
private:
    // Private member functions for each complaint level
    void debug();
    void info();
    void warning();
    void error();

    // Typedef for a pointer to a member function
    typedef void (Harl::*ComplaintFunction)();

    // Array of function pointers
    ComplaintFunction complaintFunctions[4];

    // Array of level names
    std::string levels[4];

public:
    // Constructor
    Harl();

    // Public member function to complain
    void complain(std::string level);
};

#endif