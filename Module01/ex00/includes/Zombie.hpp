#ifndef ZOMBIE_H
# define ZOMBIE_H

#include <string>

class Phonebook {
private:
    std::string name;

public:
    Phonebook();
    Phonebook(std::string name);
    ~Phonebook();

    void        announce();
    std::string getName() const;
};


#endif
