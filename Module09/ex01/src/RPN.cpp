#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN& other) {
    _stack = other._stack;
}

RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

bool RPN::isOperator(const char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::performOperation(const char op) {
    if (_stack.size() < 2) {
        throw InvalidExpressionException();
    }

    int b = _stack.top(); _stack.pop();
    int a = _stack.top(); _stack.pop();
    int result;

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) throw DivisionByZeroException();
            result = a / b; 
            break;
        default:
            throw InvalidExpressionException();
    }
    _stack.push(result);
}

void RPN::processToken(const std::string& token) {
    if (token.length() == 1 && isOperator(token[0])) {
        performOperation(token[0]);
    } else {
        // Check if it's a number
        for (size_t i = 0; i < token.length(); ++i) {
            if (!isdigit(token[i])) {
                throw InvalidExpressionException();
            }
        }
        int num = atoi(token.c_str());
        _stack.push(num);
    }
}

int RPN::evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        try {
            processToken(token);
        } catch (const std::exception& e) {
            throw;
        }
    }

    if (_stack.size() != 1) {
        throw InvalidExpressionException();
    }

    return _stack.top();
}

const char* RPN::InvalidExpressionException::what() const throw() {
    return "Error";
}

const char* RPN::DivisionByZeroException::what() const throw() {
    return "Error: division by zero";
}