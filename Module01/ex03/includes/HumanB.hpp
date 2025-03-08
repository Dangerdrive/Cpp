#ifndef HUMANB_H
# define HUMANB_H

#include "Weapon.hpp"
#include <string>

class HumanB {
private:
    

public:
    HumanB();
    HumanB(const std::string _name);
    ~HumanB();
    
    std::string name;
};

#endif
