/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:18:57 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/29 19:29:00 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }
ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isChar(const std::string& literal) {
    return literal.length() == 1 && !isdigit(literal[0]);
}

bool ScalarConverter::isInt(const std::string& literal) {
    if (literal.empty()) return false;
    
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    for (; i < literal.length(); i++) {
        if (!isdigit(literal[i])) return false;
    }
    return true;
}

bool ScalarConverter::isFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") 
        return true;
    
    if (literal.empty() || literal[literal.length()-1] != 'f') 
        return false;
        
    std::string withoutF = literal.substr(0, literal.length()-1);
    size_t dotPos = withoutF.find('.');
    if (dotPos == std::string::npos || dotPos == 0 || dotPos == withoutF.length()-1)
        return false;
        
    size_t i = 0;
    if (withoutF[0] == '-' || withoutF[0] == '+') i++;
    for (; i < withoutF.length(); i++) {
        if (i != dotPos && !isdigit(withoutF[i])) return false;
    }
    return true;
}

bool ScalarConverter::isDouble(const std::string& literal) {
    if (literal == "-inf" || literal == "+inf" || literal == "nan") 
        return true;
    
    size_t dotPos = literal.find('.');
    if (dotPos == std::string::npos || dotPos == 0 || dotPos == literal.length()-1)
        return false;
        
    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    for (; i < literal.length(); i++) {
        if (i != dotPos && !isdigit(literal[i])) return false;
    }
    return true;
}

void ScalarConverter::convertFromChar(const std::string& literal) {
    char c = literal[0];
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertFromInt(const std::string& literal) {
    std::istringstream iss(literal);
    int i;
    iss >> i;

    if (i < CHAR_MIN || i > CHAR_MAX)
        std::cout << "char: impossible" << std::endl;
    else if (i < 32 || i > 126)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;

    std::cout << "int: " << i << std::endl;

    std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;

    std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
}

void ScalarConverter::convertFromFloat(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << literal << std::endl;
        std::cout << "double: " << literal.substr(0, literal.length()-1) << std::endl;
        return;
    }
    
    std::string withoutF = literal.substr(0, literal.length()-1);
    std::istringstream iss(withoutF);
    float f;
    iss >> f;

    if (f < CHAR_MIN || f > CHAR_MAX || isnan(f))
        std::cout << "char: impossible" << std::endl;
    else if (f < 32 || f > 126)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;

    if (f < INT_MIN || f > static_cast<float>(INT_MAX) || isnan(f))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;

    std::cout << "float: " << f;
    if (f == floor(f) && f < 1e6 && f > -1e6)
        std::cout << ".0";
    std::cout << "f" << std::endl;
    
    std::cout << "double: " << static_cast<double>(f);
    if (f == floor(f) && f < 1e6 && f > -1e6)
        std::cout << ".0";
    std::cout << std::endl;
}

void ScalarConverter::convertFromDouble(const std::string& literal) {
    if (literal == "-inf" || literal == "+inf" || literal == "nan") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << literal << "f" << std::endl;
        std::cout << "double: " << literal << std::endl;
        return;
    }
    
    std::istringstream iss(literal);
    double d;
    iss >> d;
    
    if (d < CHAR_MIN || d > CHAR_MAX || isnan(d))
        std::cout << "char: impossible" << std::endl;
    else if (d < 32 || d > 126)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
    
    if (d < INT_MIN || d > INT_MAX || isnan(d))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;
    
    std::cout << "float: " << static_cast<float>(d);
    if (d == floor(d) && d < 1e6 && d > -1e6)
        std::cout << ".0";
    std::cout << "f" << std::endl;
    
    std::cout << "double: " << d;
    if (d == floor(d) && d < 1e6 && d > -1e6)
        std::cout << ".0";
    std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& literal) {
    if (isChar(literal))
        convertFromChar(literal);
    else if (isInt(literal))
        convertFromInt(literal);
    else if (isFloat(literal))
        convertFromFloat(literal);
    else if (isDouble(literal))
        convertFromDouble(literal);
    else
        std::cerr << "Error: Invalid literal format" << std::endl;
}