/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:18:11 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 20:22:56 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "../includes/Contact.hpp"
#include "../includes/PhoneBook.hpp"

int main() {
	Phonebook phonebook;
	Contact new_contact;
	std::string command;

	std::cout << "Welcome to PhoneBook" << std::endl;

	while (1) {
		std::cout << "Enter command: ";
		std::getline(std::cin, command);

		if (command.empty()) {
			std::cout << "Error: No command entered. Please try again."
					  << std::endl;
			continue;
		}
		if (command.compare("ADD") == 0) {
			new_contact.setField("First Name");
			new_contact.setField("Last Name");
			new_contact.setField("Nickname");
			new_contact.setField("Phone Number");
			new_contact.setField("Darkest Secret");
			phonebook.AddContact(new_contact);
		} else if (command.compare("SEARCH") == 0) {
			if (phonebook.getContactCount() == 0) {
				std::cout << "No contacts added. ADD a contact first."
						  << std::endl;
			} else {
				phonebook.DisplaySearchContacts();
				phonebook.Search();
			}
			continue;
		} else if (command.compare("EXIT") == 0) {
			std::cout << "Exiting PhoneBook..." << std::endl;
			return (0);
		} else {
			std::cout << "Invalid command. Try a valid one: ADD, SEARCH or EXIT"
					  << std::endl;
		}
	}
}
