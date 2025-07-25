#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <deque>
#include <vector>
#include <set>
#include <string>

class PmergeMe
{
  public:
    PmergeMe();
    PmergeMe(const PmergeMe& pm);
    PmergeMe& operator=(const PmergeMe& pm);
    ~PmergeMe();

    void sortVector(std::vector<int>& vec);
    void sortDeque(std::deque<int>& deque);

    static int comparisonCount;
    static bool isVectorSorted(const std::vector<int>& vec);
    static bool isDequeSorted(const std::deque<int>& deque);

    // Utility functions
    static std::string validateArguments(int argc, char** argv);
    static std::vector<int> argumentsToVector(int argc, char** argv);
    static std::deque<int> argumentsToDeque(int argc, char** argv);
    static std::set<int> argumentsToSet(int argc, char** argv);
    static std::string argumentsToString(int argc, char** argv);
    static std::string vectorToString(const std::vector<int>& vec);
    static bool retainsOriginalValues(const std::set<int>& original_values, const std::vector<int>& vec);
    static void printResults(int argc, char** argv,
                           const std::vector<int>& vec,
                           double timeVec,
                           double timeDeque);

  private:
    template <typename T> void mergeInsertionSort(T& container, int pairLevel);
    template <typename T> void swapPair(T it, int pairLevel);
};

long jacobsthalNumber(long n);

template <typename T> bool compareIterators(T lv, T rv) {
    PmergeMe::comparisonCount++;
    return *lv < *rv;
}

template <typename T> T getNextIterator(T it, int steps) {
    std::advance(it, steps);
    return it;
}

#endif
