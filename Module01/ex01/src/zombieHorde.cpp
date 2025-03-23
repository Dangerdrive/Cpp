/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:39 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/21 20:59:44 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/Zombie.hpp"

Zombie* zombieHorde( int N, std::string name ) {
    Zombie* horde = new Zombie[N];

    for (int i = 0; i < N; i++) {
        new (&horde[i]) Zombie (name);
    }

    return horde;
}
