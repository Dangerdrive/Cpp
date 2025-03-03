/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:54:01 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/03 18:54:04 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
