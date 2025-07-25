#include "PmergeMe.hpp"
#include <cmath>
#include <deque>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

int PmergeMe::comparisonCount = 0;

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& pm) { (void)pm; }
PmergeMe& PmergeMe::operator=(const PmergeMe& pm) { (void)pm; return *this; }
PmergeMe::~PmergeMe() {}

// Sorting functions implementation
long jacobsthalNumber(long n) {
    return round((pow(2, n + 1) + pow(-1, n)) / 3);
}

void PmergeMe::sortVector(std::vector<int>& vec) {
    mergeInsertionSort<std::vector<int> >(vec, 1);
}

void PmergeMe::sortDeque(std::deque<int>& deque) {
    mergeInsertionSort<std::deque<int> >(deque, 1);
}

template <typename T>
void PmergeMe::swapPair(T it, int pairLevel)
{
    T start = getNextIterator(it, -pairLevel + 1);
    T end = getNextIterator(start, pairLevel);
    while (start != end)
    {
        std::iter_swap(start, getNextIterator(start, pairLevel));
        start++;
    }
}

template <typename T>
void PmergeMe::mergeInsertionSort(T& container, int pairLevel)
{
    typedef typename T::iterator Iterator;

    int pairUnitsCount = container.size() / pairLevel;
    if (pairUnitsCount < 2)
        return;

    bool isOdd = pairUnitsCount % 2 == 1;
    Iterator start = container.begin();
    Iterator last = getNextIterator(container.begin(), pairLevel * (pairUnitsCount));
    Iterator end = getNextIterator(last, -(isOdd * pairLevel));

    int jump = 2 * pairLevel;
    for (Iterator it = start; it != end; std::advance(it, jump))
    {
        Iterator thisPair = getNextIterator(it, pairLevel - 1);
        Iterator nextPair = getNextIterator(it, pairLevel * 2 - 1);
        if (compareIterators(nextPair, thisPair))
        {
            swapPair(thisPair, pairLevel);
        }
    }
    mergeInsertionSort(container, pairLevel * 2);

    std::vector<Iterator> mainChain;
    std::vector<Iterator> pendingElements;

    mainChain.insert(mainChain.end(), getNextIterator(container.begin(), pairLevel - 1));
    mainChain.insert(mainChain.end(), getNextIterator(container.begin(), pairLevel * 2 - 1));

    for (int i = 4; i <= pairUnitsCount; i += 2)
    {
        pendingElements.insert(pendingElements.end(),
            getNextIterator(container.begin(), pairLevel * (i - 1) - 1));
        mainChain.insert(mainChain.end(),
            getNextIterator(container.begin(), pairLevel * i - 1));
    }

    if (isOdd)
    {
        pendingElements.insert(pendingElements.end(),
            getNextIterator(end, pairLevel - 1));
    }

    int prevJacobsthal = jacobsthalNumber(1);
    int insertedNumbers = 0;
    for (int k = 2;; k++)
    {
        int currJacobsthal = jacobsthalNumber(k);
        int jacobsthalDiff = currJacobsthal - prevJacobsthal;
        int offset = 0;
        if (jacobsthalDiff > static_cast<int>(pendingElements.size()))
            break;
        int iterations = jacobsthalDiff;
        typename std::vector<Iterator>::iterator pendIt =
            getNextIterator(pendingElements.begin(), jacobsthalDiff - 1);
        typename std::vector<Iterator>::iterator boundIt =
            getNextIterator(mainChain.begin(), currJacobsthal + insertedNumbers);
        while (iterations)
        {
            typename std::vector<Iterator>::iterator idx =
                std::upper_bound(mainChain.begin(), boundIt, *pendIt, compareIterators<Iterator>);
            typename std::vector<Iterator>::iterator inserted = mainChain.insert(idx, *pendIt);
            iterations--;
            pendIt = pendingElements.erase(pendIt);
            std::advance(pendIt, -1);
            offset += (inserted - mainChain.begin()) == currJacobsthal + insertedNumbers;
            boundIt = getNextIterator(mainChain.begin(), currJacobsthal + insertedNumbers - offset);
        }
        prevJacobsthal = currJacobsthal;
        insertedNumbers += jacobsthalDiff;
        offset = 0;
    }

    for (ssize_t i = pendingElements.size() - 1; i >= 0; i--)
    {
        typename std::vector<Iterator>::iterator currPend =
            getNextIterator(pendingElements.begin(), i);
        typename std::vector<Iterator>::iterator currBound =
            getNextIterator(mainChain.begin(), mainChain.size() - pendingElements.size() + i + isOdd);
        typename std::vector<Iterator>::iterator idx =
            std::upper_bound(mainChain.begin(), currBound, *currPend, compareIterators<Iterator>);
        mainChain.insert(idx, *currPend);
    }

    std::vector<int> copy;
    copy.reserve(container.size());
    for (typename std::vector<Iterator>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
    {
        for (int i = 0; i < pairLevel; i++)
        {
            Iterator pairStart = *it;
            std::advance(pairStart, -pairLevel + i + 1);
            copy.insert(copy.end(), *pairStart);
        }
    }

    Iterator containerIt = container.begin();
    std::vector<int>::iterator copyIt = copy.begin();
    while (copyIt != copy.end())
    {
        *containerIt = *copyIt;
        containerIt++;
        copyIt++;
    }
}

// Utility functions implementation
static std::string validateArgument(std::string arg)
{
    if (arg[0] == '-')
        return "Negative numbers are not allowed";
    long nbr = strtol(arg.c_str(), NULL, 10);
    if (nbr == 0 && arg != "0")
        return "Non-number arguments not allowed";
    if (nbr > INT_MAX || errno == ERANGE)
        return "Too big arguments are not allowed";
    return "";
}

std::string PmergeMe::validateArguments(int argc, char** argv)
{
    if (argc == 1)
        return "No arguments were provided";
    for (int i = 1; i < argc; i++)
    {
        std::string status = validateArgument(argv[i]);
        if (status != "")
            return status;
    }
    return "";
}

std::vector<int> PmergeMe::argumentsToVector(int argc, char** argv)
{
    std::vector<int> res;
    res.reserve(argc - 1);
    for (int i = 1; i < argc; i++)
    {
        res.push_back(atoi(argv[i]));
    }
    return res;
}

std::deque<int> PmergeMe::argumentsToDeque(int argc, char** argv)
{
    std::deque<int> res;
    for (int i = 1; i < argc; i++)
    {
        res.push_back(atoi(argv[i]));
    }
    return res;
}

std::set<int> PmergeMe::argumentsToSet(int argc, char** argv)
{
    std::set<int> res;
    for (int i = 1; i < argc; i++)
    {
        res.insert(atoi(argv[i]));
    }
    return res;
}

bool PmergeMe::isVectorSorted(const std::vector<int>& vec)
{
    if (vec.size() == 0 || vec.size() == 1)
        return true;
    std::vector<int>::const_iterator end = vec.end();
    std::advance(end, -1);
    for (std::vector<int>::const_iterator it = vec.begin(); it != end; it++)
    {
        std::vector<int>::const_iterator next = it;
        std::advance(next, 1);
        if (*it > *next)
            return false;
    }
    return true;
}

bool PmergeMe::isDequeSorted(const std::deque<int>& deque)
{
    if (deque.size() == 0 || deque.size() == 1)
        return true;
    std::deque<int>::const_iterator end = deque.end();
    std::advance(end, -1);
    for (std::deque<int>::const_iterator it = deque.begin(); it != end; it++)
    {
        std::deque<int>::const_iterator next = it;
        std::advance(next, 1);
        if (*it > *next)
            return false;
    }
    return true;
}

std::string PmergeMe::argumentsToString(int argc, char** argv)
{
    std::string res("");
    res.reserve(argc + 1);
    res += "[";
    res += argv[1];
    for (int i = 2; argv[i]; i++)
    {
        res += " ";
        res += argv[i];
    }
    res += "]";
    return res;
}

std::string PmergeMe::vectorToString(const std::vector<int>& vec)
{
    std::stringstream ss;
    ss << "[" << vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
        ss << " " << vec[i];
    }
    ss << "]";
    return ss.str();
}

bool PmergeMe::retainsOriginalValues(const std::set<int>& original_values, const std::vector<int>& vec)
{
    std::set<int> tempSet = original_values;
    for (int i = 0; i < (int)vec.size(); i++)
    {
        if (tempSet.find(vec[i]) == tempSet.end())
            return false;
        tempSet.erase(vec[i]);
    }
    return true;
}

void PmergeMe::printResults(int argc, char** argv,
                          const std::vector<int>& vec,
                          double timeVec,
                          double timeDeque)
{
    std::cout << "\033[31mBefore\033[00m: " << argumentsToString(argc, argv) << "\n";
    std::cout << "\033[32mAfter\033[00m:  " << vectorToString(vec) << "\n";
    std::cout << "Time to process " << vec.size()
              << " elements with vector: " << std::fixed << std::setprecision(6)
              << timeVec << "s\n";
    std::cout << "Time to process " << vec.size()
              << " elements with deque:  " << std::fixed << std::setprecision(6)
              << timeDeque << "s\n";
    //std::cout << "Number of comparisons: " << comparisonCount << '\n';
}
