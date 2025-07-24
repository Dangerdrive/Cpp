#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

class PmergeMe
{
  public:
    PmergeMe();
    PmergeMe(const PmergeMe& pm);
    PmergeMe& operator=(const PmergeMe& pm);
    ~PmergeMe();

    void sort_vec(std::vector<int>& vec);
    void sort_deque(std::deque<int>& deque);

    static int nbr_of_comps;

  private:
    void _merge_insertion_sort_vec(std::vector<int>& vec, int pair_level);
    void _merge_insertion_sort_deque(std::deque<int>& deque, int pair_level);

    void _swap_pair_vec(std::vector<int>::iterator it, int pair_level);
    void _swap_pair_deque(std::deque<int>::iterator it, int pair_level);
};

long _jacobsthal_number(long n);

#endif