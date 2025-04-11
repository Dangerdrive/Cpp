# Animal Hierarchy Exercise - Abstract Base Class

## Overview
This exercise modifies our animal hierarchy to make the base `AAnimal` class abstract, preventing direct instantiation while maintaining all polymorphic behavior. The key changes focus on proper object-oriented design principles using abstract classes and pure virtual functions.

## Key Changes from Previous Exercise

### 1. Abstract Base Class Implementation
- **Renamed to `AAnimal`**: Following common conventions for abstract classes
- **Made non-instantiable**: Can no longer create `AAnimal` objects directly
- **Pure virtual function**: Added `makeSound() = 0` to enforce implementation in derived classes

### 2. Virtual Function System
```cpp
virtual void makeSound() const = 0; // Pure virtual function
```
- **Virtual**: Enables runtime polymorphism (dynamic dispatch)
- **Pure virtual (`= 0`)**: 
  - Makes class abstract
  - Forces derived classes to implement this method
  - Cannot instantiate classes with pure virtual functions

### 3. Maintained Polymorphic Behavior
All existing functionality works exactly as before:
- `Dog` and `Cat` still inherit from `AAnimal`
- Virtual destructors ensure proper cleanup
- Polymorphic calls to `makeSound()` work as expected

## Abstract Classes Explained

### What is an Abstract Class?
- A class that cannot be instantiated directly
- Serves as a base for other classes
- Contains at least one pure virtual function
- Defines an interface that derived classes must implement

### Why Use Abstract Classes?
1. **Design Enforcement**: Ensures derived classes implement required behavior
2. **Prevent Misuse**: Makes it impossible to create generic "Animal" objects
3. **Interface Definition**: Clearly specifies what derived classes must do
4. **Polymorphism**: Enables working with derived classes through base pointers/references

## Compilation and Testing

### Building
```bash
make
```

### Testing
The main program demonstrates:
1. Attempting to instantiate `AAnimal` directly fails (commented out)
2. Polymorphic behavior with `Dog` and `Cat`
3. Proper virtual destructor calls
4. Deep copying of derived classes

### Expected Output
```
AAnimal default constructor called
Dog default constructor called
Brain default constructor called
AAnimal default constructor called
Cat default constructor called
Brain default constructor called
Dog 
Cat 
Meow meow!
Woof woof!
Dog destructor called
Brain destructor called
AAnimal destructor called
Cat destructor called
Brain destructor called
AAnimal destructor called
```

## Design Considerations

### Good Practices Demonstrated
- Abstract base class for generic concepts
- Pure virtual functions for required behaviors
- Virtual destructors in polymorphic hierarchies
- Clear compile-time errors for misuse
- Maintained all previous functionality while improving design

### Why This Matters
This exercise demonstrates crucial OOP principles:
- **Abstraction**: Hiding implementation details
- **Polymorphism**: Uniform interface for different types
- **Inheritance**: Specializing general concepts
- **Type Safety**: Preventing invalid object creation