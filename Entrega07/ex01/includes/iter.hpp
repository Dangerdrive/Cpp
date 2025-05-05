/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:25:04 by fde-alen          #+#    #+#             */
/*   Updated: 2025/05/01 15:56:03 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T>
void iter(T* array, size_t length, void (*func)(T&)) {
    for (size_t i = 0; i < length; ++i) {
        func(array[i]);
    }
}

#endif