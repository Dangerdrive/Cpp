#include <iostream>
#include "../includes/Contact.class.hpp"
#include "../includes/PhoneBook.class.hpp"

class Phonebook {
private:
    Contact Contacts[8];  // Array to store 8 contacts
    int contact_count;    // Keep track of how many contacts are stored

public:
    Phonebook();
    ~Phonebook();

    void AddContact(const Contact& contact){
    Contacts[contact_count % 8] = contact;
    contact_count++;		
	}
};
