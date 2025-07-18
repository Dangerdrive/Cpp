#include "PmergeMe.hpp"
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <climits>

int PmergeMe::_comparisonCount = 0;

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
    *this = other;
}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        this->_vec = other._vec;
        this->_deq = other._deq;
    }
    return *this;
}

bool PmergeMe::_compare(int a, int b) {
    _comparisonCount++;
    return a < b;
}

void PmergeMe::_validateInput(int argc, char** argv) {
    if (argc < 2) {
        throw std::runtime_error("Error: no input provided.");
    }

    _vec.clear();
    _deq.clear();

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.empty() || arg.find_first_not_of("0123456789") != std::string::npos) {
            throw std::runtime_error("Error: invalid input '" + arg + "'");
        }

        long num;
        std::istringstream iss(arg);
        iss >> num;
        if (num < 0 || num > INT_MAX || iss.fail() || !iss.eof()) {
            throw std::runtime_error("Error: invalid number '" + arg + "'");
        }

        _vec.push_back(static_cast<int>(num));
        _deq.push_back(static_cast<int>(num));
    }
}

size_t PmergeMe::_jacobsthal(size_t n) const {
    // Jacobsthal numbers: J(n) = J(n-1) + 2*J(n-2)
    // Sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, ...
    if (n == 0) return 0;
    if (n == 1) return 1;
    return _jacobsthal(n - 1) + 2 * _jacobsthal(n - 2);
}

// Vector implementation
void PmergeMe::_insertVec(std::vector<int>& main, std::vector<int>& pend, size_t jacobIndex) {
    size_t jacob = _jacobsthal(jacobIndex);
    size_t prevJacob = _jacobsthal(jacobIndex - 1);

    if (jacob > pend.size()) {
        if (prevJacob >= pend.size()) {
            return;
        }
        jacob = pend.size();
    }

    Compare comp(this);
    for (size_t i = jacob; i > prevJacob; --i) {
        if (i - 1 >= pend.size()) continue;

        std::vector<int>::iterator bound = main.begin() + (2 * (i - 1) + 1);
        if (bound > main.end()) bound = main.end();

        std::vector<int>::iterator pos = std::upper_bound(
            main.begin(), bound, pend[i - 1], comp);
        main.insert(pos, pend[i - 1]);
    }
}

void PmergeMe::_mergeInsertVec(std::vector<int>& vec) {
    if (vec.size() <= 1) return;

    // Step 1: Pairwise comparison
    std::vector<std::pair<int, int> > pairs;
    bool hasOdd = (vec.size() % 2 != 0);
    int odd = hasOdd ? vec.back() : -1;

    // Make sure we don't go out of bounds
    size_t pairCount = vec.size() / 2;
    for (size_t i = 0; i < pairCount; ++i) {
        size_t first = i * 2;
        size_t second = first + 1;
        if (_compare(vec[second], vec[first])) {
            pairs.push_back(std::make_pair(vec[second], vec[first]));
        } else {
            pairs.push_back(std::make_pair(vec[first], vec[second]));
        }
    }

    // Recursively sort the larger elements
    std::vector<int> largerElements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        largerElements.push_back(pairs[i].second);
    }

    _mergeInsertVec(largerElements);

    // Rebuild pairs with sorted order
    std::vector<std::pair<int, int> > sortedPairs;
    for (size_t i = 0; i < largerElements.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].second == largerElements[i]) {
                sortedPairs.push_back(pairs[j]);
                pairs.erase(pairs.begin() + j);
                break;
            }
        }
    }

    // Step 2: Build main chain and pend
    std::vector<int> main;
    std::vector<int> pend;

    main.push_back(sortedPairs[0].first);
    for (size_t i = 0; i < sortedPairs.size(); ++i) {
        main.push_back(sortedPairs[i].second);
        if (i > 0) {
            pend.push_back(sortedPairs[i].first);
        }
    }
    if (hasOdd && odd != -1) {
        pend.push_back(odd);
    }

    // Step 3: Binary insertion using Jacobsthal sequence
    Compare comp(this);
    size_t jacobIndex = 3;
    while (true) {
        size_t prevSize = pend.size();
        _insertVec(main, pend, jacobIndex);
        if (pend.size() == prevSize) break;
        jacobIndex++;
    }

    vec = main;
}

void PmergeMe::_sortVec(std::vector<int>& vec) {
    clock_t start = clock();
    _mergeInsertVec(vec);
    clock_t end = clock();
    double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << std::fixed << std::setprecision(5)
              << elapsed << " us" << std::endl;
}

// Deque implementation (similar to vector but with deque operations)
void PmergeMe::_insertDeq(std::deque<int>& main, std::deque<int>& pend, size_t jacobIndex) {
    size_t jacob = _jacobsthal(jacobIndex);
    size_t prevJacob = _jacobsthal(jacobIndex - 1);

    if (jacob > pend.size()) {
        if (prevJacob >= pend.size()) {
            return;
        }
        jacob = pend.size();
    }

    Compare comp(this);
    for (size_t i = jacob; i > prevJacob; --i) {
        if (i - 1 >= pend.size()) continue;

        std::deque<int>::iterator bound = main.begin() + (2 * (i - 1) + 1);
        if (bound > main.end()) bound = main.end();

        std::deque<int>::iterator pos = std::upper_bound(
            main.begin(), bound, pend[i - 1], comp);
        main.insert(pos, pend[i - 1]);
    }
}

void PmergeMe::_mergeInsertDeq(std::deque<int>& deq) {
    if (deq.size() <= 1) return;

    std::vector<std::pair<int, int> > pairs;
    bool hasOdd = deq.size() % 2 != 0;
    int odd = hasOdd ? deq.back() : 0;

    for (size_t i = 0; i < deq.size() - hasOdd; i += 2) {
        if (_compare(deq[i + 1], deq[i])) {
            pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
        } else {
            pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
        }
    }

    std::vector<int> largerElements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        largerElements.push_back(pairs[i].second);
    }

    _mergeInsertVec(largerElements); // Reuse vector implementation for recursive sorting

    std::vector<std::pair<int, int> > sortedPairs;
    for (size_t i = 0; i < largerElements.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].second == largerElements[i]) {
                sortedPairs.push_back(pairs[j]);
                pairs.erase(pairs.begin() + j);
                break;
            }
        }
    }

    std::deque<int> main;
    std::deque<int> pend;

    main.push_back(sortedPairs[0].first);
    for (size_t i = 0; i < sortedPairs.size(); ++i) {
        main.push_back(sortedPairs[i].second);
        if (i > 0) {
            pend.push_back(sortedPairs[i].first);
        }
    }
    if (hasOdd) pend.push_back(odd);

    size_t jacobIndex = 3;
    while (true) {
        size_t prevSize = pend.size();
        _insertDeq(main, pend, jacobIndex);
        if (pend.size() == prevSize) break;
        jacobIndex++;
    }

    deq = main;
}

void PmergeMe::_sortDeq(std::deque<int>& deq) {
    clock_t start = clock();
    _mergeInsertDeq(deq);
    clock_t end = clock();
    double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque  : " << std::fixed << std::setprecision(5)
              << elapsed << " us" << std::endl;
}

int PmergeMe::getComparisonCount() {
    return _comparisonCount;
}

void PmergeMe::resetComparisonCount() {
    _comparisonCount = 0;
}

void PmergeMe::sort(int argc, char** argv) {
    resetComparisonCount();
    _validateInput(argc, argv);

    std::vector<int> vecCopy = _vec;
    std::deque<int> deqCopy = _deq;

    std::cout << "Before: ";
    for (size_t i = 0; i < vecCopy.size(); ++i) {
        std::cout << vecCopy[i] << " ";
    }
    std::cout << std::endl;

    _sortVec(_vec);
    _sortDeq(_deq);

    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); ++i) {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;

    // Verify both containers produced the same result
    if (_vec != std::vector<int>(_deq.begin(), _deq.end())) {
        throw std::runtime_error("Error: vector and deque implementations produced different results");
    }
}
