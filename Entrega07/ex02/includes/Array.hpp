/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:12:52 by fde-alen          #+#    #+#             */
/*   Updated: 2025/05/01 19:24:03 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstdlib>

template <typename T>
class Array {
private:
    T* _array;
    unsigned int _size;

public:
    Array();
    Array(unsigned int n);
    Array(const Array& other);
    ~Array();
    Array& operator=(const Array& other);

    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

    unsigned int size() const;

    class OutOfBoundsException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

#include "Array.tpp"

#endif