#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <exception>

class RPN {
private:
    std::stack<int> _stack;
    
    bool isOperator(const char c) const;
    void performOperation(const char op);
    void processToken(const std::string& token);

public:
    RPN();
    RPN(const RPN& other);
    ~RPN();
    RPN& operator=(const RPN& other);

    int evaluate(const std::string& expression);
    
    class InvalidExpressionException : public std::exception {
        public: virtual const char* what() const throw();
    };
    
    class DivisionByZeroException : public std::exception {
        public: virtual const char* what() const throw();
    };
};

#endif