# Understanding `std::stack` for the Reverse Polish Notation (RPN) Exercise

The `std::stack` container is essential for implementing the RPN calculator efficiently. Here's why and how it's used:

## Key Features of `std::stack` Relevant to This Exercise

1. **LIFO Principle**:
   - Last-In-First-Out data structure
   - Perfect for RPN evaluation where we need to access the most recent operands first
   - Operations always work with the top elements of the stack

2. **Simple Interface**:
   - `push()`: Add element to top
   - `pop()`: Remove top element
   - `top()`: Access top element
   - `size()`: Check number of elements

3. **Efficiency**:
   - All operations are O(1) time complexity
   - No random access needed for RPN evaluation

## How `std::stack` is Used in the Solution

### 1. Storing Operands

```cpp
std::stack<int> _stack;
```

- Stores integer operands during evaluation
- Numbers are pushed onto the stack as they're encountered
- When operators are found, operands are popped from the stack

### 2. Processing Tokens

```cpp
void RPN::processToken(const std::string& token) {
    if (token.length() == 1 && isOperator(token[0])) {
        performOperation(token[0]);  // Operator - perform calculation
    } else {
        // Number - push to stack
        int num = atoi(token.c_str());
        _stack.push(num);
    }
}
```

- Numbers are pushed onto the stack
- Operators trigger calculations using the top stack elements

### 3. Performing Operations

```cpp
void RPN::performOperation(const char op) {
    if (_stack.size() < 2) {
        throw InvalidExpressionException();
    }

    int b = _stack.top(); _stack.pop();
    int a = _stack.top(); _stack.pop();
    int result;
    
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) throw DivisionByZeroException();
            result = a / b; 
            break;
    }
    _stack.push(result);
}
```

- Pops two operands (top element is second operand)
- Performs the operation
- Pushes result back onto stack

### 4. Evaluating the Expression

```cpp
int RPN::evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        processToken(token);
    }

    if (_stack.size() != 1) {
        throw InvalidExpressionException();
    }

    return _stack.top();
}
```

- Processes each token sequentially
- Final result should be the only remaining stack element
- Any other stack state indicates an invalid expression

## Why `std::stack` is Ideal for RPN

1. **Natural Fit for RPN**:
   - RPN is inherently stack-based
   - Operations always work with the most recent values
   - No need for complex parsing or operator precedence

2. **Error Detection**:
   - Easy to check for invalid expressions (not enough operands)
   - Clear when operations can/cannot be performed

3. **Efficiency**:
   - Single pass through the expression
   - Minimal memory usage
   - Constant time operations

## Important Stack Operations Used

1. **Pushing Values**:
   ```cpp
   _stack.push(num);
   ```

2. **Accessing Top Element**:
   ```cpp
   int val = _stack.top();
   ```

3. **Removing Top Element**:
   ```cpp
   _stack.pop();
   ```

4. **Checking Size**:
   ```cpp
   if (_stack.size() < 2) // Need at least 2 operands
   ```

## Alternative Containers Considered

While `std::stack` is perfect for this exercise, other containers could be considered:

1. `std::vector`:
   - Could simulate stack operations
   - But provides unnecessary functionality
   - Less clear intent in code

2. `std::deque`:
   - Similar performance characteristics
   - Again, provides unnecessary functionality

3. Plain array with index:
   - Would need manual size management
   - More error-prone
   - No bounds checking

The `std::stack` provides the cleanest abstraction for this use case with no performance penalty.