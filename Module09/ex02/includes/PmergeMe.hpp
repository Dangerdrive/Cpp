#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <sys/time.h>
#include <deque>
#include <iomanip>
#include <iostream>
#include <vector>

class MergeInsertSorter {
private:
    std::vector<int> m_vectorData;
    std::deque<int> m_dequeData;

    // Vector sorting methods
    void sortUsingVector();
    void sortEachVectorPair();
    void mergeSortVectorPairs(std::vector<std::pair<int, int> >& pairs);
    void mergeVectorPairs(const std::vector<std::pair<int, int> >& left,
                        const std::vector<std::pair<int, int> >& right,
                        std::vector<std::pair<int, int> >& merged);
    void binaryInsertionSortVector(std::vector<int>& mainChain, std::vector<int>& pendingElements);
    void insertElementVector(std::vector<int>& chain, int value, int upperBound);

    // Deque sorting methods
    void sortUsingDeque();
    void sortEachDequePair();
    void mergeSortDequePairs(std::deque<std::pair<int, int> >& pairs);
    void mergeDequePairs(const std::deque<std::pair<int, int> >& left,
                        const std::deque<std::pair<int, int> >& right,
                        std::deque<std::pair<int, int> >& merged);
    void binaryInsertionSortDeque(std::deque<int>& mainChain, std::deque<int>& pendingElements);
    void insertElementDeque(std::deque<int>& chain, int value, int upperBound);

    // Helper methods
    void printSequence(const std::vector<int>& sequence) const;
    void printSequence(const std::deque<int>& sequence) const;
    int calculateNextJacobsthalNumber(int previous) const;
    bool isAlreadySorted() const;

public:
    MergeInsertSorter(const std::vector<int>& vectorInput, const std::deque<int>& dequeInput);
    MergeInsertSorter(const MergeInsertSorter& other);
    MergeInsertSorter& operator=(const MergeInsertSorter& other);
    ~MergeInsertSorter();

    void performSorting();
};

#endif