/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:15:00 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 15:35:27 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft {

/*
** =============================== ENABLE_IF ================================ **
*/

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };

/*
** ============================== IS_INTEGRAL =============================== **
*/

struct true_type {
	static const bool value = true; 
};

struct false_type {
	static const bool value = false; 
};

template <class T>
struct is_integral: public false_type { };

template <> struct is_integral<bool>               : public true_type { };
template <> struct is_integral<char>               : public true_type { };
template <> struct is_integral<unsigned char>      : public true_type { };
template <> struct is_integral<wchar_t>            : public true_type { };
template <> struct is_integral<short>              : public true_type { }; // same as char16_t
template <> struct is_integral<int>                : public true_type { }; // same as char32_t
template <> struct is_integral<long>               : public true_type { };
template <> struct is_integral<long long>          : public true_type { };
template <> struct is_integral<unsigned short>     : public true_type { };
template <> struct is_integral<unsigned int>       : public true_type { };
template <> struct is_integral<unsigned long>      : public true_type { };
template <> struct is_integral<unsigned long long> : public true_type { };

// More type traits
// template<class T, class U>
// struct is_same { enum { value = 0 }; }; // could use a static const bool value = false; (prettier)
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
