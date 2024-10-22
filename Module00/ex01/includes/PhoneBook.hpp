#ifndef PHONEBOOK_CLASS_H
# define PHONEBOOK_CLASS_H

#include "Contact.hpp"

class Phonebook {
private:
    Contact Contacts[8];
    int contact_count;

public:
    Phonebook();
    ~Phonebook();

    int getContactCount() const;
    void AddContact(const Contact& contact);
    void PrintColumn(std::string text) const;
    void PrintContactForSearch(Contact contact, std::string index) const;
    void DisplaySearchContacts() const;
    void PrintFullContact(const Contact& contact) const;
    void Search() const;
};


#endif