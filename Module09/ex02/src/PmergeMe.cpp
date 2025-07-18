#include "PmergeMe.hpp"
#include <algorithm>
#include <ctime>

MergeInsertSorter::MergeInsertSorter(const std::vector<int>& vectorInput, 
                                   const std::deque<int>& dequeInput) 
    : m_vectorData(vectorInput), m_dequeData(dequeInput) {}

MergeInsertSorter::MergeInsertSorter(const MergeInsertSorter& other) {
    *this = other;
}

MergeInsertSorter& MergeInsertSorter::operator=(const MergeInsertSorter& other) {
    if (this != &other) {
        m_vectorData = other.m_vectorData;
        m_dequeData = other.m_dequeData;
    }
    return *this;
}

MergeInsertSorter::~MergeInsertSorter() {}

void MergeInsertSorter::performSorting() {
    struct timeval startTime, endTime;

    if (isAlreadySorted()) {
        std::cout << "Sequence is already sorted. No sorting performed." << std::endl;
        return;
    }

    std::cout << "\nBefore sorting: ";
    printSequence(m_vectorData);

    // Vector sorting
    gettimeofday(&startTime, NULL);
    sortUsingVector();
    gettimeofday(&endTime, NULL);
    
    std::cout << "After sorting (vector): ";
    printSequence(m_vectorData);
    std::cout << "Time to process " << m_vectorData.size() << " elements with vector: "
              << std::fixed << std::setprecision(6)
              << (endTime.tv_sec - startTime.tv_sec) + 
                 (endTime.tv_usec - startTime.tv_usec) * 1e-6 << " us\n";

    // Deque sorting
    gettimeofday(&startTime, NULL);
    sortUsingDeque();
    gettimeofday(&endTime, NULL);
    
    std::cout << "Time to process " << m_dequeData.size() << " elements with deque: "
              << std::fixed << std::setprecision(6)
              << (endTime.tv_sec - startTime.tv_sec) + 
                 (endTime.tv_usec - startTime.tv_usec) * 1e-6 << " us\n";
}

// Vector implementation
void MergeInsertSorter::sortUsingVector() {
    if (m_vectorData.size() < 2) return;

    std::vector<std::pair<int, int> > pairs;
    std::vector<int> mainChain;
    std::vector<int> pendingElements;

    sortEachVectorPair();

    // Create pairs
    for (size_t i = 1; i < m_vectorData.size(); i += 2) {
        pairs.emplace_back(m_vectorData[i-1], m_vectorData[i]);
    }

    // Sort pairs recursively
    mergeSortVectorPairs(pairs);

    // Separate into main chain and pending elements
    for (const auto& pair : pairs) {
        mainChain.push_back(pair.first);
        pendingElements.push_back(pair.second);
    }

    binaryInsertionSortVector(mainChain, pendingElements);

    // Handle odd element if exists
    if (m_vectorData.size() % 2 == 1) {
        insertElementVector(mainChain, m_vectorData.back(), mainChain.size() - 1);
    }
    
    m_vectorData = mainChain;
}

void MergeInsertSorter::sortEachVectorPair() {
    for (auto it = m_vectorData.begin() + 1; it < m_vectorData.end(); it += 2) {
        if (*(it - 1) < *it) {
            std::iter_swap(it - 1, it);
        }
    }
}

void MergeInsertSorter::mergeSortVectorPairs(std::vector<std::pair<int, int> >& pairs) {
    if (pairs.size() <= 1) return;

    size_t mid = pairs.size() / 2;
    std::vector<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
    std::vector<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());

    mergeSortVectorPairs(left);
    mergeSortVectorPairs(right);

    pairs.clear();
    mergeVectorPairs(left, right, pairs);
}

void MergeInsertSorter::mergeVectorPairs(const std::vector<std::pair<int, int> >& left,
                                       const std::vector<std::pair<int, int> >& right,
                                       std::vector<std::pair<int, int> >& merged) {
    size_t leftIdx = 0, rightIdx = 0;

    while (leftIdx < left.size() && rightIdx < right.size()) {
        if (left[leftIdx].first <= right[rightIdx].first) {
            merged.push_back(left[leftIdx++]);
        } else {
            merged.push_back(right[rightIdx++]);
        }
    }

    while (leftIdx < left.size()) merged.push_back(left[leftIdx++]);
    while (rightIdx < right.size()) merged.push_back(right[rightIdx++]);
}

void MergeInsertSorter::binaryInsertionSortVector(std::vector<int>& mainChain, 
                                                std::vector<int>& pendingElements) {
    size_t lower = 1;
    size_t upper = (pendingElements.size() > 2) ? 2 : pendingElements.size() - 1;
    size_t current = upper;

    mainChain.insert(mainChain.begin(), pendingElements[0]);

    while (lower < pendingElements.size()) {
        insertElementVector(mainChain, pendingElements[current], upper + lower - 1);
        
        if (current == lower) {
            lower = upper + 1;
            upper = (calculateNextJacobsthalNumber(upper + 1) > static_cast<int>(pendingElements.size()))
                   ? pendingElements.size() - 1
                   : calculateNextJacobsthalNumber(upper + 1) - 1;
            current = upper;
        } else {
            current--;
        }
    }
}

void MergeInsertSorter::insertElementVector(std::vector<int>& chain, int value, int upperBound) {
    int low = 0;
    int high = (chain.size() < static_cast<size_t>(upperBound)) ? chain.size() : upperBound;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (chain[mid] == value) {
            chain.insert(chain.begin() + mid + 1, value);
            return;
        } else if (chain[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    chain.insert(chain.begin() + low, value);
}

// Deque implementation (similar structure to vector but with deque)
void MergeInsertSorter::sortUsingDeque() {
    if (m_dequeData.size() < 2) return;

    std::deque<std::pair<int, int> > pairs;
    std::deque<int> mainChain;
    std::deque<int> pendingElements;

    sortEachDequePair();

    // Create pairs from deque elements
    for (size_t i = 1; i < m_dequeData.size(); i += 2) {
        pairs.emplace_back(m_dequeData[i-1], m_dequeData[i]);
    }

    // Sort pairs recursively
    mergeSortDequePairs(pairs);

    // Separate into main chain (larger elements) and pending elements (smaller elements)
    for (const auto& pair : pairs) {
        mainChain.push_back(pair.first);
        pendingElements.push_back(pair.second);
    }

    // Perform binary insertion sort on the pending elements
    binaryInsertionSortDeque(mainChain, pendingElements);

    // Handle odd element if exists
    if (m_dequeData.size() % 2 == 1) {
        insertElementDeque(mainChain, m_dequeData.back(), mainChain.size() - 1);
    }
    
    m_dequeData = mainChain;
}

void MergeInsertSorter::sortEachDequePair() {
    for (auto it = m_dequeData.begin() + 1; it < m_dequeData.end(); it += 2) {
        if (*(it - 1) < *it) {
            std::iter_swap(it - 1, it);
        }
    }
}

void MergeInsertSorter::mergeSortDequePairs(std::deque<std::pair<int, int> >& pairs) {
    if (pairs.size() <= 1) return;

    size_t mid = pairs.size() / 2;
    std::deque<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
    std::deque<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());

    mergeSortDequePairs(left);
    mergeSortDequePairs(right);

    pairs.clear();
    mergeDequePairs(left, right, pairs);
}

void MergeInsertSorter::mergeDequePairs(const std::deque<std::pair<int, int> >& left,
                                      const std::deque<std::pair<int, int> >& right,
                                      std::deque<std::pair<int, int> >& merged) {
    size_t leftIdx = 0, rightIdx = 0;

    while (leftIdx < left.size() && rightIdx < right.size()) {
        if (left[leftIdx].first <= right[rightIdx].first) {
            merged.push_back(left[leftIdx++]);
        } else {
            merged.push_back(right[rightIdx++]);
        }
    }

    while (leftIdx < left.size()) merged.push_back(left[leftIdx++]);
    while (rightIdx < right.size()) merged.push_back(right[rightIdx++]);
}

void MergeInsertSorter::binaryInsertionSortDeque(std::deque<int>& mainChain, 
                                               std::deque<int>& pendingElements) {
    size_t lower = 1;
    size_t upper = (pendingElements.size() > 2) ? 2 : pendingElements.size() - 1;
    size_t current = upper;

    mainChain.insert(mainChain.begin(), pendingElements[0]);

    while (lower < pendingElements.size()) {
        insertElementDeque(mainChain, pendingElements[current], upper + lower - 1);
        
        if (current == lower) {
            lower = upper + 1;
            upper = (calculateNextJacobsthalNumber(upper + 1) > static_cast<int>(pendingElements.size()))
                   ? pendingElements.size() - 1
                   : calculateNextJacobsthalNumber(upper + 1) - 1;
            current = upper;
        } else {
            current--;
        }
    }
}

void MergeInsertSorter::insertElementDeque(std::deque<int>& chain, int value, int upperBound) {
    int low = 0;
    int high = (chain.size() < static_cast<size_t>(upperBound)) ? chain.size() : upperBound;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (chain[mid] == value) {
            chain.insert(chain.begin() + mid + 1, value);
            return;
        } else if (chain[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    chain.insert(chain.begin() + low, value);
}

// Helper methods
void MergeInsertSorter::printSequence(const std::vector<int>& sequence) const {
    for (int num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void MergeInsertSorter::printSequence(const std::deque<int>& sequence) const {
    for (int num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int MergeInsertSorter::calculateNextJacobsthalNumber(int previous) const {
    int n1 = 0;
    int n2 = 1;
    int next = previous;

    while (true) {
        next = 2 * n1 + n2;
        n1 = n2;
        n2 = next;
        if (next > previous) return next;
    }
}

bool MergeInsertSorter::isAlreadySorted() const {
    for (size_t i = 1; i < m_vectorData.size(); ++i) {
        if (m_vectorData[i-1] > m_vectorData[i]) {
            return false;
        }
    }
    return true;
}