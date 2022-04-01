/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:16:16 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 17:18:00 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

template <class T1, class T2>
struct pair {
	// Member types
	typedef T1	first_type;
	typedef T2	second_type;

	// Member objects (public)
	first_type	first;
	second_type	second;

	//	### Member functions
	//[(constructor)](https://en.cppreference.com/w/cpp/utility/pair/pair "cpp/utility/pair/pair")
	//constructs new pair
	// 1) Default constructor. Value-initializes both elements of the pair, first and second.
	pair(): first(), second() { }
	// 2) Initializes first with x and second with y.
	pair( const T1& x, const T2& y ): first(x), second(y) { }
	// 5) Initializes first with p.first and second with p.second.
	template< class U1, class U2 >
	pair( const pair<U1, U2>& p ): first(p.first), second(p.second) { }
	// 9) Copy constructor is implicitly declared (until C++11) defaulted, and is constexpr
	// if copying of both elements satisfies the requirements on constexpr functions (since C++11).
	// pair( const pair& p );

	//[operator=](https://en.cppreference.com/w/cpp/utility/pair/operator%3D "cpp/utility/pair/operator=")
	//assigns the contents
	// 1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
	// The assignment operator is implicitly declared. (until c++11)
	// Using this assignment operator makes the program ill-formed if either T1 or T2 is a const-qualified type,
	// or a reference type, or a class type with an inaccessible copy assignment operator, or an array type of such class.
	// Example of explicit definition:
	// pair& operator=( const pair& other ) {
	// 	if (&other == this)
	// 		return (*this);
	// 	first = other.first;
	// 	second = other.second;
	// 	return (*this);
	// }
};

//### Non-member functions
//[make_pair](https://en.cppreference.com/w/cpp/utility/pair/make_pair "cpp/utility/pair/make pair")
//creates a `pair` object of type, defined by the argument types
template< class T1, class T2 >
pair<T1,T2> make_pair( T1 t, T2 u ) {
	return (pair<T1, T2>(t, u));
}

//[operators](https://en.cppreference.com/w/cpp/utility/pair/operator_cmp "cpp/utility/pair/operator cmp")
//lexicographically compares the values in the pair
template< class T1, class T2 >
bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
	return(lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class T1, class T2 >
bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
	return(lhs.first != rhs.first || lhs.second != rhs.second);
}

template< class T1, class T2 >
bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
	if (lhs.first != rhs.first)
		return (lhs.first < rhs.first);
	else
		return (lhs.second < rhs.second);
}

template< class T1, class T2 >
bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
	if (lhs.first != rhs.first)
		return (lhs.first <= rhs.first);
	else
		return (lhs.second <= rhs.second);
}

template< class T1, class T2 >
bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
	return (!(lhs <= rhs));
}

template< class T1, class T2 >
bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ){
	return (!(lhs < rhs));
}

}

#endif
