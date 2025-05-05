### Understanding `.tpp` Files in C++ Templates

In C++ projects, especially those using templates, you might encounter `.tpp` files. These are used to implement template classes or functions while keeping the declaration and definition separate for better code organization. Here's a detailed explanation:

---

### **1. Why Separate Template Declarations and Definitions?**
By default, C++ requires template definitions to be visible at the point of instantiation (where they're used). This means:
- If you put template definitions in a `.cpp` file, the compiler won't see them when compiling other files, leading to **linker errors**.
- The common solution is to define templates entirely in header files (`.hpp`), but this can make headers large and harder to read.

A `.tpp` file provides a clean way to:
- Keep declarations in `.hpp` (clean interface).
- Move definitions to `.tpp` (implementation details).
- Include the `.tpp` at the **end** of the `.hpp` (ensuring definitions are visible).

---

### **2. How `.tpp` Files Work**
#### **File Structure**
1. **`Array.hpp` (Declaration)**  
   - Contains the class template declaration.
   - At the bottom, it includes `Array.tpp` to pull in the definitions.

   ```cpp
   #ifndef ARRAY_HPP
   #define ARRAY_HPP

   template <typename T>
   class Array {
   public:
       Array();                          // Declaration
       T& operator[](unsigned int idx);  // Declaration
       // ...
   };

   #include "Array.tpp"  // Pull in definitions
   #endif
   ```

2. **`Array.tpp` (Definitions)**  
   - Contains the actual implementations of the template members.

   ```cpp
   template <typename T>
   Array<T>::Array() { /* ... */ }  // Definition

   template <typename T>
   T& Array<T>::operator[](unsigned int idx) { /* ... */ }  // Definition
   ```

3. **`main.cpp` (Usage)**  
   - Just includes `Array.hpp`. The `.tpp` definitions are automatically included.

   ```cpp
   #include "Array.hpp"

   int main() {
       Array<int> arr(10);
       return 0;
   }
   ```

---

### **3. Key Advantages**
#### **Cleaner Code Organization**
- **Separation of concerns**: Declarations (interface) in `.hpp`, definitions (implementation) in `.tpp`.
- **Easier navigation**: Users of the class only need to look at `.hpp` for the API.

#### **Avoids Linker Errors**
- Since `.tpp` is included in `.hpp`, the compiler sees the full template definition when instantiated (no "missing symbol" errors).

#### **Explicit Template Instantiation (Optional)**
- If you know you’ll only use a few types (e.g., `int`, `float`), you can explicitly instantiate them in a `.cpp` file:
  ```cpp
  // Explicit instantiations (in Array.cpp)
  template class Array<int>;
  template class Array<float>;
  ```
  - This reduces compile times by avoiding recompiling the template for each use.

---

### **4. Comparison to Alternatives**
| Approach               | Pros                          | Cons                          |
|------------------------|-------------------------------|-------------------------------|
| **All in `.hpp`**      | Simple, no linker errors      | Bloated headers               |
| **`.hpp` + `.tpp`**    | Clean separation              | Slightly more files           |
| **Explicit instantiation** | Faster compilation       | Inflexible (fixed types)      |

---

### **5. When to Use `.tpp` Files**
- **Template-heavy projects**: Keeps code organized.
- **Large templates**: Splits complex logic from declarations.
- **Library code**: Users only see the `.hpp` interface.

---

### **Example from Your Exercise**
In your `Array` class:
- `Array.hpp` declares the class and its members.
- `Array.tpp` defines the member functions (e.g., `operator[]`, constructors).
- `main.cpp` includes `Array.hpp` and uses the template.

This ensures:
1. The compiler sees the definitions when needed.
2. The header remains clean and focused on the interface.

---

### **Key Takeaway**
`.tpp` files are a **convention** (not a C++ requirement) to manage template code neatly. They solve the "template definition visibility" problem while improving code organization. Use them when:
- You want to separate interface/implementation for templates.
- You want to avoid monolithic `.hpp` files.