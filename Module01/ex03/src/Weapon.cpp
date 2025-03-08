#include "../includes/Weapon.hpp"

std::string& Weapon::getType() const { return this->type&; }
void Weapon::setType(std::string& NewType) {
	this->type = newType;
}