

class methods are private by default
structs are public by default.

cpp9 - containers
map
stack

lista vector/deck

modern C++
Use std::unique_ptr or std::shared_ptr instead of raw pointers whenever possible.

Smart pointers automatically manage memory and set themselves to nullptr when the memory is freed.

#include <memory>
std::unique_ptr<int> ptr = std::make_unique<int>(42);



Since smart pointers are not available in C++98, you can use the following techniques to manage memory safely:

1. RAII (Resource Acquisition Is Initialization)
RAII is a programming idiom where resources (e.g., memory) are tied to the lifetime of an object.

When the object goes out of scope, its destructor automatically releases the resource.

Example:

cpp
Copy
class MyInt {
private:
    int* ptr;
public:
    MyInt(int value) : ptr(new int(value)) {}
    ~MyInt() { delete ptr; }
    int get() const { return *ptr; }
};

int main() {
    MyInt obj(42); // Memory is managed by the MyInt object
    std::cout << obj.get() << std::endl;
    // Memory is automatically freed when obj goes out of scope
    return 0;
}
2. Custom Smart Pointer
You can implement your own simple smart pointer in C++98.

Example:

cpp
Copy
template <typename T>
class SimplePtr {
private:
    T* ptr;
public:
    explicit SimplePtr(T* p = nullptr) : ptr(p) {}
    ~SimplePtr() { delete ptr; }
    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    // Disable copy constructor and assignment operator
    SimplePtr(const SimplePtr&) = delete;
    SimplePtr& operator=(const SimplePtr&) = delete;
};

int main() {
    SimplePtr<int> ptr(new int(42));
    std::cout << *ptr << std::endl;
    // Memory is automatically freed when ptr goes out of scope
    return 0;
}


What is a Function Template?
A function template is a blueprint for creating functions. It uses placeholders (called template parameters) for types, which are replaced by actual types when the function is called.

Syntax of a Function Template
cpp
Copy
template <typename T>
T add(T a, T b) {
    return a + b;
}
Here:

template <typename T>: This declares a template with a single type parameter T.

T: A placeholder for the type. It can be any type (e.g., int, double, std::string, etc.).

add(T a, T b): A function that takes two parameters of type T and returns a value of type T.

How Function Templates Work
When you call a function template, the compiler instantiates a version of the function for the specific type you use.

Example:

cpp
Copy
int main() {
    int result1 = add(3, 5); // T is int
    double result2 = add(2.5, 3.7); // T is double
    std::cout << result1 << ", " << result2 << std::endl; // Output: 8, 6.2
    return 0;
}
Here:

add(3, 5) instantiates add<int>.

add(2.5, 3.7) instantiates add<double>.

Why Function Templates Must Be in Header Files
Template Instantiation:

Templates are not actual code until they are instantiated with a specific type.

The compiler needs to see the full definition of the template (not just a declaration) to generate the code for the specific type.



References
References are safer and easier to use than pointers because they cannot be null and cannot be reassigned to refer to a different variable.

A reference is an alias for a variable and shares its memory address.

They are often used in function parameters to avoid copying large objects.




module 01 - ex04

The line:

cpp
std::ifstream inputFile(filename.c_str());
is used to create an std::ifstream object (inputFile) and open a file for reading. Let’s break it down step by step:

1. std::ifstream
std::ifstream is a class in the C++ Standard Library that represents an input file stream.

It is used to read data from files.

2. inputFile
inputFile is an instance of the std::ifstream class.

It will be used to interact with the file specified by filename.

3. filename.c_str()
filename is a std::string object that contains the name of the file to be opened.

The c_str() member function of std::string returns a C-style string (a const char*) that represents the content of the std::string.

This is necessary because the std::ifstream constructor expects a C-style string (a const char*) as its argument, not a std::string.

4. std::ifstream inputFile(filename.c_str());
This line creates an std::ifstream object named inputFile and attempts to open the file specified by filename.

The constructor of std::ifstream takes a const char* (a C-style string) as its argument, which is why filename.c_str() is used to convert the std::string to a C-style string.




reading from a file
std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Read the entire file content into a string
    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

writing to a file
std::ofstream outputFile(filename.c_str());
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }

    // Write the content to the file
    outputFile << content;
    outputFile.close();    