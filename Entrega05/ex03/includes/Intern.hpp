/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:42:29 by marvin            #+#    #+#             */
/*   Updated: 2025/04/17 22:04:13 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include <string>

class Intern {
public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    AForm* makeForm(const std::string& formName, const std::string& target);

private:
    typedef AForm* (Intern::*FormCreator)(const std::string& target);

    AForm* createShrubberyCreationForm(const std::string& target);
    AForm* createRobotomyRequestForm(const std::string& target);
    AForm* createPresidentialPardonForm(const std::string& target);

    struct FormType {
        std::string name;
        FormCreator creator;
    };

    static const FormType formTypes[3];
};

#endif
