#ifndef HUMANA_H
# define HUMANA_H

#include "Weapon.hpp"
#include <string>

class HumanA {
private:
    

public:
    HumanA();
    HumanA(const std::string _name, const std::string _weapon_type);
    ~HumanA();
    
    std::string name;
    Weapon::WeaponA;

};

#endif
