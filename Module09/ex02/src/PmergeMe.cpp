#include "PmergeMe.hpp"
#include <cmath>
#include <algorithm>
#include <climits>

int PmergeMe::nbr_of_comps = 0;

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const std::vector<int>& vec, const std::deque<int>& deq) 
    : m_vector(vec), m_deque(deq) {}
PmergeMe::PmergeMe(const PmergeMe& pm) { *this = pm; }
PmergeMe& PmergeMe::operator=(const PmergeMe& pm) {
    if (this != &pm) {
        m_vector = pm.m_vector;
        m_deque = pm.m_deque;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}

void PmergeMe::sort() {
    merge_insertion_sort_vec(m_vector, 1);
    merge_insertion_sort_deque(m_deque, 1);
}

std::ostream& operator<<(std::ostream& os, const PmergeMe& pm) {
    os << "Vector: [";
    for (size_t i = 0; i < pm.m_vector.size(); ++i) {
        if (i != 0) os << " ";
        os << pm.m_vector[i];
    }
    os << "]\nDeque: [";
    for (size_t i = 0; i < pm.m_deque.size(); ++i) {
        if (i != 0) os << " ";
        os << pm.m_deque[i];
    }
    os << "]";
    return os;
}

long jacobsthal_number(long n) {
    return (long)((pow(2.0, n + 1) + pow(-1.0, n)) / 3.0 + 0.5);
}

void PmergeMe::sort_vec(std::vector<int>& vec) {
    merge_insertion_sort_vec(vec, 1);
}

void PmergeMe::sort_deque(std::deque<int>& deque) {
    merge_insertion_sort_deque(deque, 1);
}

void PmergeMe::swap_pair_vec(std::vector<int>::iterator it, int pair_level) {
    std::vector<int>::iterator start = it;
    std::advance(start, -pair_level + 1);
    std::vector<int>::iterator end = start;
    std::advance(end, pair_level);
    
    while (start != end) {
        std::vector<int>::iterator next = start;
        std::advance(next, pair_level);
        std::iter_swap(start, next);
        start++;
    }
}

void PmergeMe::swap_pair_deque(std::deque<int>::iterator it, int pair_level) {
    std::deque<int>::iterator start = it;
    std::advance(start, -pair_level + 1);
    std::deque<int>::iterator end = start;
    std::advance(end, pair_level);
    
    while (start != end) {
        std::deque<int>::iterator next = start;
        std::advance(next, pair_level);
        std::iter_swap(start, next);
        start++;
    }
}

bool compare_vec_iterators(std::vector<int>::iterator lv, std::vector<int>::iterator rv) {
    PmergeMe::nbr_of_comps++;
    return *lv < *rv;
}

bool compare_deque_iterators(std::deque<int>::iterator lv, std::deque<int>::iterator rv) {
    PmergeMe::nbr_of_comps++;
    return *lv < *rv;
}

void PmergeMe::merge_insertion_sort_vec(std::vector<int>& container, int pair_level) {
    int pair_units_nbr = container.size() / pair_level;
    if (pair_units_nbr < 2) return;

    bool is_odd = pair_units_nbr % 2 == 1;
    std::vector<int>::iterator start = container.begin();
    std::vector<int>::iterator last = container.begin();
    std::advance(last, pair_level * pair_units_nbr);
    std::vector<int>::iterator end = last;
    if (is_odd) std::advance(end, -pair_level);

    int jump = 2 * pair_level;
    for (std::vector<int>::iterator it = start; it != end; std::advance(it, jump)) {
        std::vector<int>::iterator this_pair = it;
        std::advance(this_pair, pair_level - 1);
        std::vector<int>::iterator next_pair = it;
        std::advance(next_pair, pair_level * 2 - 1);
        if (compare_vec_iterators(next_pair, this_pair)) {
            swap_pair_vec(this_pair, pair_level);
        }
    }
    merge_insertion_sort_vec(container, pair_level * 2);

    std::vector<std::vector<int>::iterator> main;
    std::vector<std::vector<int>::iterator> pend;

    std::vector<int>::iterator it = container.begin();
    std::advance(it, pair_level - 1);
    main.push_back(it);

    it = container.begin();
    std::advance(it, pair_level * 2 - 1);
    main.push_back(it);

    for (int i = 4; i <= pair_units_nbr; i += 2) {
        it = container.begin();
        std::advance(it, pair_level * (i - 1) - 1);
        pend.push_back(it);

        it = container.begin();
        std::advance(it, pair_level * i - 1);
        main.push_back(it);
    }

    if (is_odd) {
        it = end;
        std::advance(it, pair_level - 1);
        pend.push_back(it);
    }

    int prev_jacobsthal = jacobsthal_number(1);
    int inserted_numbers = 0;
    for (int k = 2;; k++) {
        int curr_jacobsthal = jacobsthal_number(k);
        int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
        int offset = 0;
        if (jacobsthal_diff > static_cast<int>(pend.size())) break;
        
        std::vector<std::vector<int>::iterator>::iterator pend_it = pend.begin();
        std::advance(pend_it, jacobsthal_diff - 1);
        
        std::vector<std::vector<int>::iterator>::iterator bound_it = main.begin();
        std::advance(bound_it, curr_jacobsthal + inserted_numbers);
        
        int nbr_of_times = jacobsthal_diff;
        while (nbr_of_times) {
            std::vector<std::vector<int>::iterator>::iterator idx = 
                std::upper_bound(main.begin(), bound_it, *pend_it, compare_vec_iterators);
            
            std::vector<std::vector<int>::iterator>::iterator inserted = main.insert(idx, *pend_it);
            nbr_of_times--;
            pend_it = pend.erase(pend_it);
            std::advance(pend_it, -1);
            
            offset += (inserted - main.begin()) == curr_jacobsthal + inserted_numbers;
            bound_it = main.begin();
            std::advance(bound_it, curr_jacobsthal + inserted_numbers - offset);
        }
        prev_jacobsthal = curr_jacobsthal;
        inserted_numbers += jacobsthal_diff;
        offset = 0;
    }

    for (int i = pend.size() - 1; i >= 0; i--) {
        std::vector<std::vector<int>::iterator>::iterator curr_pend = pend.begin();
        std::advance(curr_pend, i);
        
        std::vector<std::vector<int>::iterator>::iterator curr_bound = main.begin();
        std::advance(curr_bound, main.size() - pend.size() + i + is_odd);
        
        std::vector<std::vector<int>::iterator>::iterator idx = 
            std::upper_bound(main.begin(), curr_bound, *curr_pend, compare_vec_iterators);
        main.insert(idx, *curr_pend);
    }

    std::vector<int> copy;
    for (std::vector<std::vector<int>::iterator>::iterator it = main.begin(); it != main.end(); it++) {
        for (int i = 0; i < pair_level; i++) {
            std::vector<int>::iterator pair_start = *it;
            std::advance(pair_start, -pair_level + i + 1);
            copy.push_back(*pair_start);
        }
    }

    std::vector<int>::iterator container_it = container.begin();
    for (std::vector<int>::iterator copy_it = copy.begin(); copy_it != copy.end(); copy_it++) {
        *container_it = *copy_it;
        container_it++;
    }
}

void PmergeMe::merge_insertion_sort_deque(std::deque<int>& container, int pair_level) {
    int pair_units_nbr = container.size() / pair_level;
    if (pair_units_nbr < 2) return;

    bool is_odd = pair_units_nbr % 2 == 1;
    std::deque<int>::iterator start = container.begin();
    std::deque<int>::iterator last = container.begin();
    std::advance(last, pair_level * pair_units_nbr);
    std::deque<int>::iterator end = last;
    if (is_odd) std::advance(end, -pair_level);

    int jump = 2 * pair_level;
    for (std::deque<int>::iterator it = start; it != end; std::advance(it, jump)) {
        std::deque<int>::iterator this_pair = it;
        std::advance(this_pair, pair_level - 1);
        std::deque<int>::iterator next_pair = it;
        std::advance(next_pair, pair_level * 2 - 1);
        if (compare_deque_iterators(next_pair, this_pair)) {
            swap_pair_deque(this_pair, pair_level);
        }
    }
    merge_insertion_sort_deque(container, pair_level * 2);

    std::vector<std::deque<int>::iterator> main;
    std::vector<std::deque<int>::iterator> pend;

    std::deque<int>::iterator it = container.begin();
    std::advance(it, pair_level - 1);
    main.push_back(it);

    it = container.begin();
    std::advance(it, pair_level * 2 - 1);
    main.push_back(it);

    for (int i = 4; i <= pair_units_nbr; i += 2) {
        it = container.begin();
        std::advance(it, pair_level * (i - 1) - 1);
        pend.push_back(it);

        it = container.begin();
        std::advance(it, pair_level * i - 1);
        main.push_back(it);
    }

    if (is_odd) {
        it = end;
        std::advance(it, pair_level - 1);
        pend.push_back(it);
    }

    int prev_jacobsthal = jacobsthal_number(1);
    int inserted_numbers = 0;
    for (int k = 2;; k++) {
        int curr_jacobsthal = jacobsthal_number(k);
        int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
        int offset = 0;
        if (jacobsthal_diff > static_cast<int>(pend.size())) break;
        
        std::vector<std::deque<int>::iterator>::iterator pend_it = pend.begin();
        std::advance(pend_it, jacobsthal_diff - 1);
        
        std::vector<std::deque<int>::iterator>::iterator bound_it = main.begin();
        std::advance(bound_it, curr_jacobsthal + inserted_numbers);
        
        int nbr_of_times = jacobsthal_diff;
        while (nbr_of_times) {
            std::vector<std::deque<int>::iterator>::iterator idx = 
                std::upper_bound(main.begin(), bound_it, *pend_it, compare_deque_iterators);
            
            std::vector<std::deque<int>::iterator>::iterator inserted = main.insert(idx, *pend_it);
            nbr_of_times--;
            pend_it = pend.erase(pend_it);
            std::advance(pend_it, -1);
            
            offset += (inserted - main.begin()) == curr_jacobsthal + inserted_numbers;
            bound_it = main.begin();
            std::advance(bound_it, curr_jacobsthal + inserted_numbers - offset);
        }
        prev_jacobsthal = curr_jacobsthal;
        inserted_numbers += jacobsthal_diff;
        offset = 0;
    }

    for (int i = pend.size() - 1; i >= 0; i--) {
        std::vector<std::deque<int>::iterator>::iterator curr_pend = pend.begin();
        std::advance(curr_pend, i);
        
        std::vector<std::deque<int>::iterator>::iterator curr_bound = main.begin();
        std::advance(curr_bound, main.size() - pend.size() + i + is_odd);
        
        std::vector<std::deque<int>::iterator>::iterator idx = 
            std::upper_bound(main.begin(), curr_bound, *curr_pend, compare_deque_iterators);
        main.insert(idx, *curr_pend);
    }

    std::deque<int> copy;
    for (std::vector<std::deque<int>::iterator>::iterator it = main.begin(); it != main.end(); it++) {
        for (int i = 0; i < pair_level; i++) {
            std::deque<int>::iterator pair_start = *it;
            std::advance(pair_start, -pair_level + i + 1);
            copy.push_back(*pair_start);
        }
    }

    std::deque<int>::iterator container_it = container.begin();
    for (std::deque<int>::iterator copy_it = copy.begin(); copy_it != copy.end(); copy_it++) {
        *container_it = *copy_it;
        container_it++;
    }
}