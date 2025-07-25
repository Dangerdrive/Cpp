#include "PmergeMe.hpp"
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <set>

int main(int argc, char** argv)
{
    PmergeMe pm;

    std::string status = PmergeMe::validateArguments(argc, argv);
    if (status != "")
    {
        std::cerr << "Error: " << status << "\n";
        return EXIT_FAILURE;
    }
    std::set<int> original_values = PmergeMe::argumentsToSet(argc, argv);

    clock_t start_vec = clock();
    std::vector<int> vec = PmergeMe::argumentsToVector(argc, argv);
    pm.sortVector(vec);
    clock_t end_vec = clock();
    double time_elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;

    PmergeMe::comparisonCount = 0;
    clock_t start_deque = clock();
    std::deque<int> deque = PmergeMe::argumentsToDeque(argc, argv);
    pm.sortDeque(deque);
    clock_t end_deque = clock();
    double time_elapsed_deque = static_cast<double>(end_deque - start_deque) / CLOCKS_PER_SEC;

    if (!PmergeMe::isVectorSorted(vec) || (int)deque.size() != (argc - 1) || !PmergeMe::retainsOriginalValues(original_values, vec))
    {
        std::cout << "Vector was not sorted properly.\n";
        return 1;
    }
    if (!PmergeMe::isDequeSorted(deque) || (int)deque.size() != (argc - 1))
    {
        std::cout << "Deque was not sorted properly.\n";
        return 1;
    }

    PmergeMe::printResults(argc, argv, vec, time_elapsed_vec, time_elapsed_deque);

}
