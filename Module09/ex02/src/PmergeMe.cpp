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
    if (n == 0) return 0;
    if (n == 1) return 1;
    return _jacobsthal(n - 1) + 2 * _jacobsthal(n - 2);
}

// Vector implementation
void PmergeMe::_insertVec(std::vector<int>& main, std::vector<int>& pend) {
    Compare comp(this);
    size_t jacobIndex = 3;

    while (!pend.empty()) {
        size_t jacob = _jacobsthal(jacobIndex);
        size_t prevJacob = _jacobsthal(jacobIndex - 1);
        size_t start = std::min(prevJacob, pend.size());
        size_t end = std::min(jacob, pend.size());

        if (start >= end) {
            jacobIndex++;
            continue;
        }

        for (size_t i = end; i > start; --i) {
            size_t pos = i - 1;
            if (pos >= pend.size()) {
                continue;
            }

            std::vector<int>::iterator bound = main.begin() + (2 * pos + 1);
            if (bound > main.end()) {
                bound = main.end();
            }

            std::vector<int>::iterator insert_pos = std::upper_bound(
                main.begin(), bound, pend[pos], comp);
            main.insert(insert_pos, pend[pos]);
            pend.erase(pend.begin() + pos);
        }
        jacobIndex++;
    }
}

void PmergeMe::_mergeInsertVec(std::vector<int>& vec, bool topLevel) {
    (void)topLevel; // Silence unused parameter warning
    if (vec.size() <= 1) return;

    std::vector<std::pair<int, int> > pairs;
    bool hasOdd = (vec.size() % 2 != 0);
    int odd = hasOdd ? vec.back() : -1;

    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        if (_compare(vec[i+1], vec[i])) {
            pairs.push_back(std::make_pair(vec[i+1], vec[i]));
        } else {
            pairs.push_back(std::make_pair(vec[i], vec[i+1]));
        }
    }

    std::vector<int> largerElements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        largerElements.push_back(pairs[i].second);
    }
    _mergeInsertVec(largerElements, false);

    std::vector<int> main;
    std::vector<int> pend;
    
    main.push_back(pairs[0].first);
    for (size_t i = 0; i < largerElements.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].second == largerElements[i]) {
                main.push_back(largerElements[i]);
                if (j != 0) {
                    pend.push_back(pairs[j].first);
                }
                break;
            }
        }
    }
    
    if (hasOdd && odd != -1) {
        pend.push_back(odd);
    }

    _insertVec(main, pend);
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

// Deque implementation
void PmergeMe::_insertDeq(std::deque<int>& main, std::deque<int>& pend) {
    Compare comp(this);
    size_t jacobIndex = 3;

    while (!pend.empty()) {
        size_t jacob = _jacobsthal(jacobIndex);
        size_t prevJacob = _jacobsthal(jacobIndex - 1);
        size_t start = std::min(prevJacob, pend.size());
        size_t end = std::min(jacob, pend.size());

        if (start >= end) {
            jacobIndex++;
            continue;
        }

        for (size_t i = end; i > start; --i) {
            size_t pos = i - 1;
            if (pos >= pend.size()) {
                continue;
            }

            std::deque<int>::iterator bound = main.begin() + (2 * pos + 1);
            if (bound > main.end()) {
                bound = main.end();
            }

            std::deque<int>::iterator insert_pos = std::upper_bound(
                main.begin(), bound, pend[pos], comp);
            main.insert(insert_pos, pend[pos]);
            pend.erase(pend.begin() + pos);
        }
        jacobIndex++;
    }
}

void PmergeMe::_mergeInsertDeq(std::deque<int>& deq, bool topLevel) {
    (void)topLevel; // Silence unused parameter warning
    if (deq.size() <= 1) return;

    std::vector<std::pair<int, int> > pairs;
    bool hasOdd = deq.size() % 2 != 0;
    int odd = hasOdd ? deq.back() : -1;

    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
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

    _mergeInsertVec(largerElements, false);

    std::deque<int> main;
    std::deque<int> pend;

    main.push_back(pairs[0].first);
    for (size_t i = 0; i < largerElements.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].second == largerElements[i]) {
                main.push_back(largerElements[i]);
                if (j != 0) {
                    pend.push_back(pairs[j].first);
                }
                break;
            }
        }
    }
    if (hasOdd && odd != -1) pend.push_back(odd);

    _insertDeq(main, pend);
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

    if (_vec != std::vector<int>(_deq.begin(), _deq.end())) {
        throw std::runtime_error("Error: vector and deque implementations produced different results");
    }
}