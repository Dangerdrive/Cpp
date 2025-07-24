#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <climits>

static bool validateInput(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        char* end;
        long num = strtol(argv[i], &end, 10);
        if (*end != '\0' || num <= 0 || num > INT_MAX) {
            std::cerr << "Error: Invalid input \"" << argv[i] << "\"\n";
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <positive integers...>\n";
        return 1;
    }

    if (!validateInput(argc, argv)) {
        return 1;
    }

    // Create containers from input
    std::vector<int> vec;
    std::deque<int> deq;
    
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        vec.push_back(num);
        deq.push_back(num);
    }

    // Create PmergeMe object with the containers
    PmergeMe sorter(vec, deq);
    
    // Display before sorting
    std::cout << "Before:\n" << sorter << std::endl;
    
    // Sort and measure time
    clock_t start = clock();
    sorter.sort();
    clock_t end = clock();
    double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    // Display after sorting
    std::cout << "After:\n" << sorter << std::endl;
    std::cout << "Time to process " << vec.size() << " elements: " 
              << std::fixed << elapsed << "s\n";
    
    return 0;
}