#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <set>
#include <string>
#include <ctime>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& pm);
    PmergeMe& operator=(const PmergeMe& pm);
    ~PmergeMe();

    // Sorting functions
    void sortVector(std::vector<int>& vec);
    void sortDeque(std::deque<int>& deque);

    // Utility functions
    static std::string validateArguments(int argc, char** argv);
    static std::vector<int> argumentsToVector(int argc, char** argv);
    static std::deque<int> argumentsToDeque(int argc, char** argv);
    static std::set<int> argumentsToSet(int argc, char** argv);
    static std::string argumentsToString(int argc, char** argv);
    static std::string vectorToString(const std::vector<int>& vec);
    static bool isVectorSorted(const std::vector<int>& vec);
    static bool isDequeSorted(const std::deque<int>& deque);
    static bool retainsOriginalValues(const std::set<int>& original_values, const std::vector<int>& vec);

    // Combined operations
    static std::set<int> sortAndTime(PmergeMe& pm, int argc, char** argv,
                                   std::vector<int>& vec,
                                   std::deque<int>& deque,
                                   double& timeVec,
                                   double& timeDeque);
    static bool validateResults(int argc,
                              const std::vector<int>& vec,
                              const std::deque<int>& deque,
                              const std::set<int>& originalValues);
    static void printResults(int argc, char** argv,
                           const std::vector<int>& vec,
                           double timeVec,
                           double timeDeque);

    static int comparisonCount;

private:
    template <typename T> void mergeInsertionSort(T& container, int pairLevel);
    template <typename T> void swapPair(T it, int pairLevel);
    template <typename T> T getNextIterator(T it, int steps);
};

template <typename T>
bool compareIterators(T lv, T rv);

long jacobsthalNumber(long n);

#endif
