/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:48:57 by fde-alen          #+#    #+#             */
/*   Updated: 2025/07/25 01:48:58 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
    PmergeMe pm;

    std::string status = PmergeMe::validateArguments(argc, argv);
    if (status != "") {
        std::cerr << "Error: " << status << "\n";
        return EXIT_FAILURE;
    }

    std::vector<int> vec;
    std::deque<int> deque;
    double timeVec, timeDeque;

    std::set<int> original_values = PmergeMe::sortAndTime(pm, argc, argv, vec, deque, timeVec, timeDeque);

    if (!PmergeMe::validateResults(argc, vec, deque, original_values)) {
        return EXIT_FAILURE;
    }

    PmergeMe::printResults(argc, argv, vec, timeVec, timeDeque);

    return EXIT_SUCCESS;
}
