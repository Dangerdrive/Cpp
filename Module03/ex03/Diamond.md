### **Inheritance Structure in the Project**
This project demonstrates **multiple inheritance** and **virtual inheritance** in C++. Here's the hierarchy:

```
        ClapTrap (Base Class)
         /       \
        /         \
  ScavTrap      FragTrap
   (virtual)    (virtual)
        \         /
         \       /
        DiamondTrap
```

#### **1. Base Class: `ClapTrap`**
- Contains core attributes (`_name`, `_hitPoints`, `_energyPoints`, `_attackDamage`).
- Defines basic functions (`attack()`, `takeDamage()`, `beRepaired()`).

#### **2. Intermediate Classes: `ScavTrap` and `FragTrap`**
- Both inherit (virtually) from `ClapTrap`.
- Each overrides `attack()` and adds unique functions:
  - `ScavTrap`: `guardGate()`
  - `FragTrap`: `highFivesGuys()`

#### **3. Derived Class: `DiamondTrap`**
- Inherits from **both `ScavTrap` and `FragTrap`** (multiple inheritance).
- Uses `virtual` inheritance to avoid the **"diamond problem"** (explained below).

---

### **Why Virtual Inheritance?**
#### **The Diamond Problem**
Without `virtual` inheritance:
```
        ClapTrap
         /     \
  ScavTrap   FragTrap
         \     /
        DiamondTrap
```
- `DiamondTrap` would contain **two copies** of `ClapTrap` (one from `ScavTrap`, one from `FragTrap`).
- This causes ambiguity (e.g., which `_name` or `_hitPoints` should `DiamondTrap` use?).

#### **Solution: `virtual` Inheritance**
By declaring `ScavTrap` and `FragTrap` as `virtual` inheritors of `ClapTrap`:
```cpp
class ScavTrap : virtual public ClapTrap { ... };
class FragTrap : virtual public ClapTrap { ... };
```
- Ensures `DiamondTrap` gets **only one shared instance** of `ClapTrap`.
- Avoids duplication and ambiguity.

---

### **Key Observations in the Code**
1. **`DiamondTrap` Initialization**
   - Calls `ClapTrap`'s constructor **explicitly** (to set the `_clap_name`):
     ```cpp
     DiamondTrap::DiamondTrap(const std::string& name) 
         : ClapTrap(name + "_clap_name"), FragTrap(), ScavTrap() { ... }
     ```
   - Uses `FragTrap::_hitPoints` and `ScavTrap::_energyPoints` to resolve conflicts.

2. **Function Overrides**
   - `DiamondTrap::attack()` calls `ScavTrap::attack()` to avoid ambiguity:
     ```cpp
     void DiamondTrap::attack(const std::string& target) {
         ScavTrap::attack(target); // Explicitly choose ScavTrap's version
     }
     ```

3. **`whoAmI()` Function**
   - Shows the difference between `DiamondTrap`'s name and `ClapTrap`'s name:
     ```cpp
     void DiamondTrap::whoAmI() {
         std::cout << "DiamondTrap name: " << _name 
                   << ", ClapTrap name: " << ClapTrap::_name << std::endl;
     }
     ```

---

### **Summary**
- **Virtual inheritance** prevents duplicate `ClapTrap` subobjects in `DiamondTrap`.
- **Multiple inheritance** allows `DiamondTrap` to combine features of `ScavTrap` and `FragTrap`.
- **Explicit scope resolution (`ScavTrap::attack()`)** avoids ambiguity in function calls.

This design ensures:
✅ No duplication of `ClapTrap` members.  
✅ Clear access to overridden functions.  
✅ Correct initialization order (base classes → derived classes).  

The project complies with C++ best practices for complex inheritance hierarchies.