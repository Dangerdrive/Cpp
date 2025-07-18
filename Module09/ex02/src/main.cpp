#include "PmergeMe.hpp"
#include <cstdlib>
#include <ctime>
#include <deque>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <sequence of positive integers>\n";
        return 1;
    }

    std::vector<int> vecInput;
    std::deque<int> deqInput;

    try {
        for (int i = 1; i < argc; ++i) {
            int num = std::atoi(argv[i]);
            if (num <= 0) throw std::invalid_argument("Only positive integers allowed");
            vecInput.push_back(num);
            deqInput.push_back(num);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    MergeInsertSorter sorter(vecInput, deqInput);
    sorter.performSorting();

    return 0;
}