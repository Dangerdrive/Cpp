#ifndef PHONEBOOK_CLASS_H
# define PHONEBOOK_CLASS_H

#include "Contact.class.hpp"

class Phonebook {
private:
    Contact Contacts[8];  // Array to store 8 contacts
    int contact_count;    // Keep track of how many contacts are stored

public:
    Phonebook();
    ~Phonebook();

    void AddContact(const Contact& contact);  // Add contact by reference
};


#endif