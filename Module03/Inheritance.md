# Inheritance and Polymorphism in C++

Inheritance and polymorphism are two fundamental concepts in object-oriented programming (OOP) that allow you to create reusable and extensible code. In the `ScavTrap` example, these concepts are used to extend the functionality of the `ClapTrap` class. Below is a detailed explanation of how inheritance and polymorphism are applied in this context.

---

## **1. Inheritance**

### **What is Inheritance?**
Inheritance is a mechanism in C++ that allows a class (called the **derived class**) to inherit attributes and behaviors (member variables and functions) from another class (called the **base class**). This promotes code reuse and establishes a hierarchical relationship between classes.

### **How is Inheritance Used in `ScavTrap`?**
- `ScavTrap` is derived from `ClapTrap` using `public` inheritance:
  ```cpp
  class ScavTrap : public ClapTrap {
  ```
  This means:
  - `ScavTrap` inherits all `public` and `protected` members of `ClapTrap`.
  - `ScavTrap` can override `ClapTrap`'s member functions (e.g., `attack()`).

### **Key Points**
- **Base Class (`ClapTrap`)**: Provides common functionality (e.g., `attack()`, `takeDamage()`, `beRepaired()`).
- **Derived Class (`ScavTrap`)**: Extends the base class by adding new functionality (e.g., `guardGate()`) and overriding existing functionality (e.g., `attack()`).

---

## **2. Polymorphism**

### **What is Polymorphism?**
Polymorphism allows objects of different classes to be treated as objects of a common base class. It enables a single interface to represent different underlying forms (data types).

### **How is Polymorphism Used in `ScavTrap`?**
- **Function Overriding**: `ScavTrap` overrides the `attack()` function from `ClapTrap` to provide its own implementation:
  ```cpp
  void ScavTrap::attack(const std::string& target) {
      if (_hitPoints == 0 || _energyPoints == 0) {
          std::cout << "ScavTrap " << _name << " can't attack. No hit points or energy points left!" << std::endl;
          return;
      }
      _energyPoints--; // Attack costs 1 energy point
      std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
  }
  ```
  This allows `ScavTrap` to have a different behavior for `attack()` compared to `ClapTrap`.

- **Dynamic Binding**: If you use a pointer or reference to the base class (`ClapTrap`) to call an overridden function (e.g., `attack()`), the derived class's implementation will be executed. This is known as **runtime polymorphism**.

---

## **3. Construction and Destruction Chaining**

### **What is Construction/Destruction Chaining?**
When a derived class object is created or destroyed, the base class's constructor and destructor are automatically called. This ensures proper initialization and cleanup of both the base and derived parts of the object.

### **How is Chaining Demonstrated in `ScavTrap`?**
- **Construction**:
  - When a `ScavTrap` object is created, the `ClapTrap` constructor is called first, followed by the `ScavTrap` constructor.
  ```cpp
  ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
      _hitPoints = 100;
      _energyPoints = 50;
      _attackDamage = 20;
      std::cout << "ScavTrap " << _name << " constructor called" << std::endl;
  }
  ```

- **Destruction**:
  - When a `ScavTrap` object is destroyed, the `ScavTrap` destructor is called first, followed by the `ClapTrap` destructor.
  ```cpp
  ScavTrap::~ScavTrap() {
      std::cout << "ScavTrap " << _name << " destructor called" << std::endl;
  }
  ```

### **Why is Chaining Important?**
- Ensures that the base class is properly initialized before the derived class.
- Ensures that resources are cleaned up in the correct order (derived class first, then base class).

---

## **4. Why Use `protected` Instead of `private`?**

- **`private`**: Members are only accessible within the class itself.
- **`protected`**: Members are accessible within the class itself and by derived classes.

Since `ScavTrap` needs to access the member variables of `ClapTrap`, these variables should be declared as `protected`.

## **5. Example Code**

### **File: `ClapTrap.hpp`**
```cpp
#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
protected:
    std::string _name;
    unsigned int _hitPoints;
    unsigned int _energyPoints;
    unsigned int _attackDamage;

public:
    ClapTrap();
    ClapTrap(const std::string& name);
    ClapTrap(const ClapTrap& other);
    ~ClapTrap();

    ClapTrap& operator=(const ClapTrap& other);

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};

#endif
```

### **File: `ScavTrap.hpp`**
```cpp
#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
    ScavTrap();
    ScavTrap(const std::string& name);
    ScavTrap(const ScavTrap& other);
    ~ScavTrap();

    ScavTrap& operator=(const ScavTrap& other);

    void attack(const std::string& target); // Override
    void guardGate(); // Unique to ScavTrap
};

#endif
```

### **File: `main.cpp`**
```cpp
#include "ScavTrap.hpp"
#include <iostream>

int main() {
    ScavTrap scav1("Scavvy");
    ScavTrap scav2("Trapster");

    scav1.attack("Trapster");
    scav2.takeDamage(20);

    scav2.beRepaired(10);

    scav1.guardGate();

    return 0;
}
```

---

## **6. Summary**

- **Inheritance**: `ScavTrap` inherits from `ClapTrap`, reusing its attributes and behaviors.
- **Polymorphism**: `ScavTrap` overrides the `attack()` function to provide its own implementation.
- **Construction/Destruction Chaining**: Ensures proper initialization and cleanup of base and derived class parts.
- **Code Reusability**: Inheritance allows `ScavTrap` to reuse `ClapTrap`'s functionality while extending it with new features.

By using inheritance and polymorphism, you can create a hierarchy of classes that share common functionality while allowing for customization and extension. This makes your code more modular, reusable, and easier to maintain.




