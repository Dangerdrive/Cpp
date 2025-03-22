/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:09:43 by fde-alen          #+#    #+#             */
/*   Updated: 2025/03/21 21:42:20 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
private:
    int _value; // Stores the fixed-point number value
    static const int _fractionalBits = 8; // Number of fractional bits (always 8)

public:
    Fixed(); // Default constructor
    Fixed(const int value); // Constructor that takes an int
    Fixed(const float value); // Constructor that takes a float
    Fixed(const Fixed& other); // Copy constructor
    Fixed& operator=(const Fixed& other); // Copy assignment operator
    ~Fixed(); // Destructor

    int getRawBits() const; // Returns the raw value of the fixed-point number
    void setRawBits(int const raw); // Sets the raw value of the fixed-point number

    float toFloat() const; // Converts fixed-point value to float
    int toInt() const; // Converts fixed-point value to int

    // Overload the insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Fixed& obj);
};

#endif
