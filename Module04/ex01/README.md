# Animal Hierarchy Exercise - Brain Implementation

## Overview
This exercise extends our animal hierarchy by adding a `Brain` class to `Dog` and `Cat` objects, introducing composition and more complex memory management. The key focus is on proper resource handling and deep copying in polymorphic hierarchies.

## Key Additions from First Exercise

### 1. New Brain Class
```cpp
class Brain {
private:
    std::string ideas[100]; // Array of 100 ideas
    // ... constructors, destructor, etc.
};
```
- Each `Dog` and `Cat` now contains a `Brain`
- Brain stores 100 ideas as strings
- Demonstrates composition (has-a relationship)

### 2. Memory Management
**Critical Changes:**
- `Dog`/`Cat` constructors now allocate a new `Brain`
- Destructors properly delete the `Brain`
- Copy constructors and assignment operators perform **deep copies** of the Brain

```cpp
// In Dog copy constructor
Dog::Dog(const Dog& other) : Animal(other) {
    brain = new Brain(*other.brain); // Deep copy
}
```

### 3. Deep Copy Requirements
- Copies must be independent (no shared Brains)
- Assignment operators must handle self-assignment
- All memory must be properly freed

## Exercise Objectives

### Primary Goals
1. **Composition**: Implement "has-a" relationships (Animal has Brain)
2. **Memory Management**: Proper allocation/deallocation in polymorphic hierarchy
3. **Deep Copying**: Ensure copied objects have independent Brains
4. **Destruction Order**: Verify proper cleanup sequence

### Key Concepts Demonstrated
- **Ownership semantics**: Each Dog/Cat owns its Brain
- **Rule of Three**: Implement copy constructor, assignment operator, and destructor
- **Polymorphic destruction**: Virtual destructors working with composition
- **Const correctness**: Proper use of const in accessors

## Testing Approach

### Verification Methods
1. **Memory Leaks**: Run with valgrind or similar tool
2. **Deep Copy Test**:
   - Modify one animal's Brain
   - Verify the other remains unchanged
3. **Destruction Order**:
   - Confirm Brain is destroyed before Animal
4. **Assignment Test**:
   - Verify self-assignment safety
   - Check independent Brains after assignment

### Example Test Output
```
Animal default constructor called
Dog default constructor called
Brain default constructor called
Animal default constructor called
Cat default constructor called
Brain default constructor called
[Animal sounds...]
Dog destructor called
Brain destructor called
Animal destructor called
Cat destructor called
Brain destructor called
Animal destructor called
```

## Important Implementation Details

### Critical Code Sections
1. **Brain Allocation** (Constructor):
```cpp
Dog::Dog() {
    brain = new Brain(); // Each Dog gets its own Brain
}
```

2. **Proper Cleanup** (Destructor):
```cpp
Dog::~Dog() {
    delete brain; // Essential to prevent leaks
}
```

3. **Deep Copy** (Copy Constructor):
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    brain = new Brain(*other.brain); // Deep copy, not shallow
}
```

4. **Assignment Operator**:
```cpp
Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {  // Check for self-assignment
        Animal::operator=(other);
        delete brain;      // Free existing brain
        brain = new Brain(*other.brain); // New deep copy
    }
    return *this;
}
```

## Design Considerations

### Why This Matters
1. **Real-world relevance**: Objects often contain other complex objects
2. **Memory safety**: Prevents leaks and dangling pointers
3. **Polymorphic correctness**: Maintains proper behavior in hierarchies
4. **Copy semantics**: Ensures independent object state

### Best Practices Demonstrated
- Always pair `new` with `delete`
- Implement full Rule of Three with composition
- Deep copy for contained objects
- Self-assignment checks
- Clear ownership semantics