# Behavior of Non-Virtual Methods in Inheritance

If `makeSound()` in the base `Animal` class wasn't declared as `virtual`, the behavior would be fundamentally different, even if derived classes appear to override it. Here's what would happen:

## Key Differences Without `virtual`

### 1. Compile-Time Binding (Static Dispatch)
Without `virtual`, method calls are resolved at **compile time** based on the **reference/pointer type**, not the actual object type.

```cpp
Animal* animal = new Dog();
animal->makeSound(); // Calls Animal::makeSound(), not Dog::makeSound()
delete animal;
```

### 2. Method Hiding (Not Overriding)
Derived class methods with the same name would **hide** rather than **override** the base class method:

```cpp
Dog dog;
dog.makeSound(); // Calls Dog::makeSound() - but only because we're using concrete type
Animal& animalRef = dog;
animalRef.makeSound(); // Calls Animal::makeSound() - not polymorphic!
```

### 3. No Runtime Polymorphism
The crucial polymorphic behavior would be lost:
```cpp
void makeAnimalSound(Animal& a) {
    a.makeSound(); // Always calls Animal::makeSound()
}

Dog d;
Cat c;
makeAnimalSound(d); // Animal sound!
makeAnimalSound(c); // Animal sound!
```

## Your Specific Example Analysis

Given your header files:

### Animal.hpp (non-virtual version)
```cpp
void makeSound() const; // NOT virtual
```

### Dog.hpp/Cat.hpp
```cpp
virtual void makeSound() const; // virtual here is irrelevant
```

### What Actually Happens:
1. **Base Class Method is Non-Virtual**:
   - `Animal::makeSound()` determines the binding behavior
   - The `virtual` in derived classes is ineffective because the base version isn't virtual

2. **Unexpected Behavior**:
   ```cpp
   Animal* animals[2];
   animals[0] = new Dog();
   animals[1] = new Cat();
   
   animals[0]->makeSound(); // Calls Animal::makeSound()
   animals[1]->makeSound(); // Calls Animal::makeSound()
   ```

## Why This Matters

### Real-World Implications:
1. **Broken Polymorphism**: Treating different animals uniformly wouldn't work
2. **Unexpected Behavior**: Code appears correct but doesn't work as intended
3. **Maintenance Issues**: Future developers might assume polymorphism exists

### Correct Approach:
Always declare methods as `virtual` in the base class when you want:
- Runtime polymorphism
- Method overriding (not just hiding)
- The ability to call derived implementations through base pointers/references

## Demonstration Code

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    void makeSound() const { cout << "Generic animal sound\n"; }
};

class Dog : public Animal {
public:
    virtual void makeSound() const { cout << "Woof woof!\n"; }
};

int main() {
    // Case 1: Direct call - works as expected
    Dog d;
    d.makeSound(); // "Woof woof!"
    
    // Case 2: Polymorphic call - fails
    Animal* a = new Dog();
    a->makeSound(); // "Generic animal sound" - NOT polymorphic!
    delete a;
    
    // Case 3: Reference call - fails
    Animal& ref = d;
    ref.makeSound(); // "Generic animal sound"
    
    return 0;
}
```

## Key Takeaways

1. **Virtual in Base Class Controls Polymorphism**: The base class declaration determines the binding behavior
2. **Virtual in Derived Classes is Meaningless** if base isn't virtual
3. **Polymorphism Requires Virtual at the Root**: The virtual keyword must start at the level where you want polymorphism to begin
4. **Compiler Warnings**: Modern compilers may warn about this situation with messages like "overriding non-virtual function"

Always make methods virtual in the base class if you want polymorphic behavior through pointers/references to the base class.