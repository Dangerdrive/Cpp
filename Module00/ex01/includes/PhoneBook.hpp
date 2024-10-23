#ifndef PHONEBOOK_CLASS_H
# define PHONEBOOK_CLASS_H

#include "Contact.hpp"

class Zombie {
private:
    Zombie Contacts[8];
    int contact_count;

public:
    Zombie();
    ~Zombie();

    int getContactCount() const;
    void AddContact(const Zombie& contact);
    void PrintColumn(std::string text) const;
    void PrintContactForSearch(Zombie contact, std::string index) const;
    void DisplaySearchContacts() const;
    void PrintFullContact(const Zombie& contact) const;
    void Search() const;
};


#endif