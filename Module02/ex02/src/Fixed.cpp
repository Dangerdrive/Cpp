/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:31 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/17 00:08:15 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Default constructor
Fixed::Fixed() : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}

// Constructor that takes an int
Fixed::Fixed(const int value) : _value(value << _fractionalBits) {
    std::cout << "Int constructor called" << std::endl;
}

// Constructor that takes a float
Fixed::Fixed(const float value) : _value(roundf(value * (1 << _fractionalBits))) {
    std::cout << "Float constructor called" << std::endl;
}

// Copy constructor
Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other; // Use the copy assignment operator
}

// Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) { // Check for self-assignment
        this->_value = other.getRawBits();
    }
    return *this;
}

// Destructor
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

// Returns the raw value of the fixed-point number
int Fixed::getRawBits() const {
    return this->_value;
}

// Sets the raw value of the fixed-point number
void Fixed::setRawBits(int const raw) {
    this->_value = raw;
}

// Converts fixed-point value to float
float Fixed::toFloat() const {
    return (float)this->_value / (1 << _fractionalBits);
}

// Converts fixed-point value to int
int Fixed::toInt() const {
    return this->_value >> _fractionalBits;
}

// Comparison operators
bool Fixed::operator>(const Fixed& other) const {
    return this->_value > other._value;
}

bool Fixed::operator<(const Fixed& other) const {
    return this->_value < other._value;
}

bool Fixed::operator>=(const Fixed& other) const {
    return this->_value >= other._value;
}

bool Fixed::operator<=(const Fixed& other) const {
    return this->_value <= other._value;
}

bool Fixed::operator==(const Fixed& other) const {
    return this->_value == other._value;
}

bool Fixed::operator!=(const Fixed& other) const {
    return this->_value != other._value;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed& other) const {
    return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed& other) const {
    return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed& other) const {
    return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed& other) const {
    return Fixed(this->toFloat() / other.toFloat());
}

// Increment/decrement operators
Fixed& Fixed::operator++() {
    this->_value += 1; // Increment by the smallest representable ϵ
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp(*this); // Create a copy of the current object
    this->_value += 1; // Increment the current object
    return temp; // Return the copy (pre-increment value)
}

Fixed& Fixed::operator--() {
    this->_value -= 1; // Decrement by the smallest representable ϵ
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp(*this); // Create a copy of the current object
    this->_value -= 1; // Decrement the current object
    return temp; // Return the copy (pre-decrement value)
}

// Static member functions
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}

// Overload the insertion operator
std::ostream& operator<<(std::ostream& os, const Fixed& obj) {
    os << obj.toFloat();
    return os;
}
