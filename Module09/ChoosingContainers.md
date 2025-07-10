For each exercise in C++ Module 09 (STL), you'll need to use different containers from the STL (Standard Template Library). Here's a recommended approach for each exercise, keeping in mind that once you use a container in one exercise, you cannot reuse it in subsequent exercises:

### Exercise 00: Bitcoin Exchange
**Recommended Container:** `std::map`
**Why?**
- You need to store dates (as keys) and corresponding Bitcoin values (as mapped values).
- `std::map` is perfect for this because it keeps keys sorted, allowing you to efficiently find the closest date using `lower_bound` or `upper_bound`.
- Example:
  ```cpp
  std::map<std::string, float> bitcoinData; // Key: date, Value: exchange rate
  ```

### Exercise 01: Reverse Polish Notation (RPN)
**Recommended Container:** `std::stack`
**Why?**
- RPN is a stack-based algorithm where you push numbers onto the stack and pop them when encountering operators.
- `std::stack` is ideal because it provides LIFO (Last-In-First-Out) operations, which are exactly what you need for RPN evaluation.
- Example:
  ```cpp
  std::stack<int> rpnStack; // For storing operands
  ```

### Exercise 02: PmergeMe (Merge-Insert Sort)
**Required:** Two different containers.
**Recommended Containers:**
1. `std::vector`
2. `std::deque` (or `std::list`, but `std::deque` is typically more efficient for this use case)
**Why?**
- You need to implement the Ford-Johnson merge-insertion sort algorithm, which involves random access and insertion operations.
- `std::vector` is efficient for random access and cache-friendly, while `std::deque` is efficient for insertions at both ends.
- Example:
  ```cpp
  std::vector<int> vec;
  std::deque<int> deq;
  ```
- Implement the algorithm separately for both containers to compare their performance.

### Container Usage Summary:
- **Ex00:** `std::map` (for date-value pairs).
- **Ex01:** `std::stack` (for RPN evaluation).
- **Ex02:** `std::vector` and `std::deque` (or `std::list`) for merge-insert sort.

### Important Notes:
1. Once you use a container in one exercise, you cannot reuse it in later exercises. For example, if you use `std::vector` in Ex00, you cannot use it in Ex02.
2. Make sure to handle errors and edge cases as specified in each exercise.
3. The choice of containers is not strictly enforced, but the above recommendations align well with the problem requirements.

Let me know if you'd like further clarification on any of these choices!
