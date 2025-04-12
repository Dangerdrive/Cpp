# Animal Hierarchy Exercise - Abstract Base Class

## Overview
This exercise modifies our animal hierarchy to make the base `AAnimal` class abstract, preventing direct instantiation while maintaining all polymorphic behavior. The key changes focus on proper object-oriented design principles using abstract classes and pure virtual functions.

## Key Changes from Previous Exercise

### 1. Abstract Base Class Implementation
- **Renamed to `AAnimal`**: Following common conventions for abstract classes
- **Made non-instantiable**: Can no longer create `AAnimal` objects directly
- **Pure virtual function**: Added `makeSound() = 0` to enforce implementation in derived classes

### 2. Virtual Function System

The primary way to make a class abstract in C++ is by declaring at least one of its member functions as a **pure virtual function**. This is what transformed your `Animal` class into an abstract class.

## Key Mechanism:

```cpp
virtual void makeSound() const; // Regular virtual function
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




























# Making a Class Abstract in C++

Yes, the primary way to make a class abstract in C++ is by declaring at least one of its member functions as a **pure virtual function**. This is what transformed your `Animal` class into an abstract class.

## Key Mechanism:

```cpp
virtual void makeSound() const = 0;  // Pure virtual function
```

### What This Does:
1. **Makes the class abstract** (cannot be instantiated)
2. **Forces derived classes** to implement this method
3. **Creates an interface** that all concrete animals must implement

## Other Characteristics of Abstract Classes:

1. **Can Have:**
   - Other virtual methods (with implementations)
   - Non-virtual methods
   - Member variables
   - Constructors and destructors

2. **Cannot:**
   - Be instantiated directly (`Animal a;` becomes illegal)
   - Skip implementing pure virtual methods in concrete derived classes

## Your Specific Case:

### Before (Concrete Class):
```cpp
class Animal {
    // ...
    virtual void makeSound() const;  // Regular virtual function
};
```

### After (Abstract Class):
```cpp
class Animal {
    // ...
    virtual void makeSound() const = 0;  // Pure virtual function
};
```

## Important Notes:

1. **Destructors Should Still Be Virtual**:
   Even in abstract classes, if you plan to delete derived objects through base pointers:
   ```cpp
   virtual ~Animal() = default;  // Still important!
   ```

2. **Can Provide Implementation**:
   Pure virtual functions can optionally have implementations:
   ```cpp
   virtual void makeSound() const = 0;
   // Later in .cpp file:
   void Animal::makeSound() const { /* default impl */ }
   ```

3. **Difference from Interfaces**:
   - In C++, interfaces are typically implemented as abstract classes with:
     - All pure virtual methods
     - No member variables
   - Your `Animal` is more than an interface since it has `type` member

## Why This Matters in Your Exercise:

1. **Design Improvement**:
   - Makes it impossible to create generic "Animal" objects (which shouldn't exist)
   - Enforces that all animals must define how they make sound

2. **Compiler Enforcement**:
   ```cpp
   Animal a;  // Now gives compiler error
   new Animal();  // Also error
   ```

3. **Still Allows Polymorphism**:
   ```cpp
   Animal* a = new Dog();  // Still works
   a->makeSound();         // Calls Dog's implementation
   ```

The pure virtual function is the key mechanism that makes the class abstract, while maintaining all other functionality of the hierarchy.