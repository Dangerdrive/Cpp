/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identification.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:20:39 by fde-alen          #+#    #+#             */
/*   Updated: 2025/04/29 18:20:40 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFICATION_HPP
#define IDENTIFICATION_HPP

class Base {
public:
    virtual ~Base();
};

class A;
class B;
class C;

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif