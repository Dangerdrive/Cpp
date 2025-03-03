/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:54:18 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/03 18:54:19 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(int argc, char **argv) {
	std::string message;
	if (argc == 1)
		message = "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	if (argc > 1) {
		for (int i = 1; i < argc; ++i)
			message += (std::string)argv[i];
		message += "\n";
		for (std::size_t i = 0; i < message.size(); ++i)
		message[i] = std::toupper(message[i]);	
	}
	std::cout << message;
}