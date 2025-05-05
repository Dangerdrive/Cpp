/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:12:46 by fde-alen          #+#    #+#             */
/*   Updated: 2025/05/01 19:12:47 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <typename T>
Array<T>::Array() : _array(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(const Array& other) : _array(NULL), _size(0) {
    *this = other;
}

template <typename T>
Array<T>::~Array() {
    if (_array)
        delete[] _array;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        if (_array)
            delete[] _array;
        _size = other._size;
        _array = new T[_size];
        for (unsigned int i = 0; i < _size; i++)
            _array[i] = other._array[i];
    }
    return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int index) {
    if (index >= _size)
        throw OutOfBoundsException();
    return _array[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const {
    if (index >= _size)
        throw OutOfBoundsException();
    return _array[index];
}

template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}

template <typename T>
const char* Array<T>::OutOfBoundsException::what() const throw() {
    return "Index out of bounds";
}