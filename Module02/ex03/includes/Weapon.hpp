/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:13 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/15 17:09:14 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

#include <string>

class Weapon {
private:
    std::string type;

public:
    Weapon();
    Weapon(const std::string& name);
    ~Weapon();

    const std::string& getType() const;
    void setType(const std::string& newType) ;
};

#endif
