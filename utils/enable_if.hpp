/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:15:00 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 14:59:00 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

// More type traits
// template<class T, class U>
// struct is_same { enum { value = 0 }; };
//
// template<class T>
// struct is_same<T, T> { enum { value = 1 }; };
//
// template< class T >
// struct remove_const                { typedef T type; };
//
// template< class T >
// struct remove_const<const T>       { typedef T type; };
//
// template<bool B, class T, class F>
// struct conditional { typedef T type; };
//
// template<class T, class F>
// struct conditional<false, T, F> { typedef F type; };
//
// template <typename T>
// struct is_const: public is_same<T, const T> { };

}

#endif
