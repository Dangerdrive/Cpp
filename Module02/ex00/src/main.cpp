/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:10:04 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/15 17:10:05 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/Zombie.hpp"

int main() {

Zombie* zombieCat = newZombie("Oli Zombie");
zombieCat->announce();

randomChump("Gin Zombie");

delete zombieCat;
}
