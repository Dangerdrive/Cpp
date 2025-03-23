/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:12:01 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/23 12:12:35 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

class ScavTrap : public ClapTrap {
public:

    ScavTrap();
    ScavTrap(const std::string& name);
    ScavTrap(const ScavTrap& other);
    ~ScavTrap();

    ScavTrap& operator=(const ScavTrap& other);

    void attack(const std::string& target);

    void guardGate();
};

#endif
