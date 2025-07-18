# The Ford-Johnson Merge-Insertion Sort Algorithm

The Ford-Johnson algorithm, also known as merge-insertion sort, is a sophisticated comparison-based sorting algorithm that combines aspects of merge sort and insertion sort to achieve near-optimal comparison efficiency. 

Refer to this article for a detailed explanation of the algorithm: [Ford-Johnson Merge-Insertion Sort](https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91).


Here are its key aspects:

## Core Concepts

1. **Hybrid Approach**:
   - Combines merge and insertion operations
   - Designed to minimize the number of comparisons
   - Particularly efficient for small to medium-sized datasets

2. **Comparison Efficiency**:
   - One of the most comparison-efficient sorting algorithms
   - Uses fewer comparisons than standard merge or quick sorts
   - Optimal for scenarios where comparisons are expensive

## Algorithm Steps

Ex.: 7 14 12 9 33 21 16 14 1 5 6 8 27 25
 
### 1. Pairwise Comparison Phase
```cpp
for (size_t i = 0; i < vec.size() - hasOdd; i += 2) {
    if (_compare(vec[i + 1], vec[i])) {
        pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
    } else {
        pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
    }
}
```
- Compare elements in pairs
- Form ordered pairs (smaller, larger)
- Handle odd-length sequences by leaving one element unpaired

Ex.: (7 14) (12 9) (33 21) (16 14) (1 5) (6 8) (27 25)
compare and switch if necessary
- Resulting pairs: (7, 14), (9, 12), (21, 33), (14, 16), (1, 5), (6, 8), (25, 27)

### 2. Recursive Sorting
```cpp
std::vector<int> largerElements;
for (size_t i = 0; i < pairs.size(); ++i) {
    largerElements.push_back(pairs[i].second);
}
_mergeInsertVec(largerElements);  // Recursive call
```
- Recursively sort the larger elements from each pair
- This establishes a sorted "skeleton" of the sequence

You will do pair of pairs and so on, recursively until you have a single element.
(7, 14), (9, 12), (21, 33), (14, 16), (1, 5), (6, 8), (25, 27)
pair of pairs: 
(((7, 14), (9, 12)), ((21, 33), (14, 16)), ((1, 5), (6, 8))), (25, 27)
notice that we have an odd pair (25, 27).
compare the pairs and switch if necessary:(we use only the greater element of each pair)
so for (7, 14) and (9, 12) we compare 14 and 12, and switch the groups:
(((7, 12), (9, 14)), ((14, 16), (21, 33)), ((1, 5), (6, 8)))
Then we will try to do pair of pairs of pairs:
((((7, 12), (9, 14)), ((14, 16), (21, 33))) ((1, 5), (6, 8)))
but there is not enough numbers to make two of those, so we stop at this level.

### 3. Main Chain Construction
```cpp
std::vector<int> main;
std::vector<int> pend;

main.push_back(sortedPairs[0].first);
for (size_t i = 0; i < sortedPairs.size(); ++i) {
    main.push_back(sortedPairs[i].second);
    if (i > 0) {
        pend.push_back(sortedPairs[i].first);
    }
}
if (hasOdd) pend.push_back(odd);
```
- Build the "main chain" starting with the smallest element
- Collect remaining elements in the "pend" (pending insertion) sequence

Example:
first name the indexes
(7, 12), (9, 14), (14, 16), (21, 33), (1, 5), (6, 8), (25, 27)
(   b1), (   a1), (   b2), (   a2), (   b3), (   a3), (    b4)

now create the main chain:
main = {b1, a1,...,aN} = {b1, a1, a2, a3} =
(7, 12), (9, 14),  (21, 33), (6, 8)
(   b1), (   a1),  (    a2), (  a3)
and the pend = {b2, ..., bN} = {b2, b3, b4} =
(14, 16), (1, 5), (25, 27)
(   b2), (   b3), (    b4)


### 4. Jacobsthal Insertion
```cpp
size_t jacobIndex = 3;
while (true) {
    size_t prevSize = pend.size();
    _insertVec(main, pend, jacobIndex);
    if (pend.size() == prevSize) break;
    jacobIndex++;
}
```
- Use Jacobsthal numbers to determine optimal insertion order. 
You create groups of elements, and the Jacobsthal number is the one in the index of the group. 
A group can be a single element or a pair of elements, or a pair of pairs, and so on.
You group then as b1, a1, b2, a2, b3, a3...
You sort them and create the indexes. So you know know that aways b1 is < a1, bn < an and so on.
You create a main chain of elements with {b1, a1, a2..., an}. In other words, b1 and all "a"s.
You create a pend with {b2, b3, ...} and so on. All "b"s besides b1.
- Jacobsthal sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171...
- We start using index 3 of jacobsthal sequence. To know how many elements to insert, we subtract the previous jacobsthal number.
So for 3 we have 3 - 1 = 2 elements to insert.
- Insert pend elements into main chain using binary insertion:
So first you would insert b3. 3 because of jacobsthal number.
Then you would insert b2.
In the next insertion, you would insert b5, which is 5 - 3 = 2 elements to insert. Then b4.
The next jacobsthal number is 11, and 11 - 5 = 6 elements. So you would insert first b11,  then b10, b9, b8, b7, b6.
The advantage here is that at this point we know that for instance b11 is smaller than a11, so we dont have to compare it with a11 and anything after it.
Or generalazing, we know that bN is smaller than aN, so we dont have to compare it with any aN.
## Key Components

### Jacobsthal Numbers
```cpp
size_t _jacobsthal(size_t n) const {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return _jacobsthal(n - 1) + 2 * _jacobsthal(n - 2);
}
```
- Special number sequence that optimizes insertion order
- Determines which elements to insert next
- Minimizes the number of required comparisons

### Binary Insertion
```cpp
std::vector<int>::iterator pos = std::upper_bound(
    main.begin(), bound, pend[i - 1], 
    [this](int a, int b) { return _compare(a, b); }
);
main.insert(pos, pend[i - 1]);
```
- Uses binary search to find insertion points
- Maintains sorted order during insertions
- Bound restricts search range for efficiency

## Performance Characteristics

1. **Time Complexity**:
   - O(n log n) comparisons in worst case
   - More efficient than standard merge sort in terms of comparisons
   - Actual runtime depends on container used (vector vs deque)

2. **Space Complexity**:
   - O(n) additional space
   - Uses temporary storage for pairs and sequences

3. **Comparison Count**:
   - Minimizes comparisons through smart insertion order
   - Jacobsthal sequence optimizes the search space

## Implementation Notes

1. **Container Independence**:
   - Algorithm logic remains the same for both vector and deque
   - Performance differences come from container characteristics

2. **Recursive Nature**:
   - Recursively processes smaller subsequences
   - Base case handles sequences of length 1 or 2

3. **Error Handling**:
   - Validates input numbers are positive
   - Checks for proper numeric format
   - Verifies both container implementations produce identical results

The Ford-Johnson algorithm demonstrates how careful algorithm design can optimize specific operations (comparisons in this case), and how the same algorithm can perform differently based on the underlying data structure used.