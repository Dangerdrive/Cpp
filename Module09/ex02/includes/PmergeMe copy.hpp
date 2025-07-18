#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iomanip>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int> _deq;
    static int _comparisonCount;

    // Comparison functor for binary search
    struct Compare {
        PmergeMe* parent;
        Compare(PmergeMe* p) : parent(p) {}
        bool operator()(int a, int b) const {
            return parent->_compare(a, b);
        }
    };

    // Vector implementation
    void _sortVec(std::vector<int>& vec);
    void _mergeInsertVec(std::vector<int>& vec);
    void _insertVec(std::vector<int>& main, std::vector<int>& pend, size_t jacobIndex);

    // Deque implementation
    void _sortDeq(std::deque<int>& deq);
    void _mergeInsertDeq(std::deque<int>& deq);
    void _insertDeq(std::deque<int>& main, std::deque<int>& pend, size_t jacobIndex);

    // Helper functions
    size_t _jacobsthal(size_t n) const;
    bool _compare(int a, int b);
    void _validateInput(int argc, char** argv);

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    ~PmergeMe();
    PmergeMe& operator=(const PmergeMe& other);

    void sort(int argc, char** argv);
    static int getComparisonCount();
    static void resetComparisonCount();
};

#endif
