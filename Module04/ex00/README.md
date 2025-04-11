# Animal Hierarchy Exercise - Introduction to Polymorphism

## Overview
This exercise introduces fundamental object-oriented programming concepts through an animal hierarchy, with a primary focus on **polymorphism** - one of the three pillars of OOP (alongside encapsulation and inheritance).

## Key Concepts Demonstrated

### 1. Base Class and Inheritance
```cpp
class Animal {
    // Base class with virtual functions
};

class Dog : public Animal {
    // Derived class
};

class Cat : public Animal {
    // Derived class
};
```
- `Animal` serves as the base class
- `Dog` and `Cat` inherit from `Animal`
- Establishes "is-a" relationships (Dog is an Animal)

### 2. Polymorphic Behavior
The core objective is demonstrating **runtime polymorphism** through:

**Virtual Functions:**
```cpp
virtual void makeSound() const; // Base class
```
- Allows derived classes to override behavior
- Enables dynamic dispatch (calling the right version at runtime)

**Example Usage:**
```cpp
Animal* animal = new Dog();
animal->makeSound(); // Calls Dog's implementation
delete animal;
```

### 3. Virtual Destructor
```cpp
virtual ~Animal(); // Crucial for proper cleanup
```
- Ensures derived class destructors are called
- Prevents memory leaks in polymorphic hierarchies

## Exercise Objectives

### Primary Learning Goals
1. **Understand polymorphism**: Treat different objects uniformly through base class pointers/references
2. **Implement virtual functions**: Enable runtime method dispatch
3. **Recognize inheritance relationships**: Design proper class hierarchies
4. **Practice proper resource cleanup**: Use virtual destructors

### Key Polymorphism Concepts
- **Base class interface**: Common API for all animals
- **Derived class implementations**: Specific behaviors for each animal type
- **Runtime binding**: Correct function called based on actual object type
- **Extensibility**: New animal types can be added without modifying existing code

## Implementation Details

### Critical Components
1. **Virtual Function Declaration**:
```cpp
class Animal {
public:
    virtual void makeSound() const; // Enables overriding
};
```

2. **Function Overriding**:
```cpp
class Dog : public Animal {
public:
    void makeSound() const override; // Dog-specific implementation
};
```

3. **Polymorphic Usage**:
```cpp
void animalSound(const Animal& animal) {
    animal.makeSound(); // Calls appropriate version
}

// Can pass Dogs, Cats, or any Animal-derived class
```

## Testing the Implementation

### Sample Test Code
```cpp
int main() {
    Animal* animals[2];
    animals[0] = new Dog();
    animals[1] = new Cat();
    
    for (int i = 0; i < 2; ++i) {
        animals[i]->makeSound(); // Polymorphic call
        delete animals[i];       // Proper cleanup
    }
    
    return 0;
}
```

### Expected Output
```
Animal constructor
Dog constructor
Animal constructor
Cat constructor
Woof woof!
Meow meow!
Dog destructor
Animal destructor
Cat destructor
Animal destructor
```

## Why This Matters

### Real-World Applications
- Game development (different enemy behaviors)
- GUI frameworks (various UI elements)
- Payment processing (different payment methods)
- Any system needing flexible, extensible object types

### Fundamental OOP Principles
1. **Abstraction**: Hide implementation details
2. **Polymorphism**: Uniform interface for different types
3. **Inheritance**: Code reuse through hierarchical relationships
4. **Encapsulation**: Protect internal object state

This exercise establishes the foundation for understanding how polymorphic systems enable flexible, maintainable object-oriented designs.