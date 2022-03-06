/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:10:26 by mjacq             #+#    #+#             */
/*   Updated: 2022/03/06 17:36:56 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ref: https://en.cppreference.com/w/cpp/container/vector

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
public:

	// MEMBER TYPES ////////////////////////////////////////////////////////////
	//
	// value_type	T
	typedef T value_type;

	// allocator_type	Allocator
	typedef Allocator allocator_type;

	// size_type	Unsigned integer type (usually std::size_t)
	typedef std::size_t size_type;

	// difference_type	Signed integer type (usually std::ptrdiff_t)
	typedef std::ptrdiff_t difference_type;

	// reference	value_type&
	typedef value_type& reference;

	// const_reference	const value_type&
	typedef const value_type& const_reference;

	// pointer	 Allocator::pointer	(until C++11)
	typedef typename Allocator::pointer pointer;

	// const_pointer	 Allocator::const_pointer	(until C++11)
	typedef typename Allocator::const_pointer const_pointer;

	// TODO: ITERATORS /////////////////////////////////////////////////////////
	// iterator	 LegacyRandomAccessIterator and LegacyContiguousIterator to value_type (until C++20)
	//
	// const_iterator	 LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type (until C++20)
	//
	// reverse_iterator	std::reverse_iterator<iterator>
	//
	// const_reverse_iterator	std::reverse_iterator<const_iterator>

	// MEMBER FUNCTIONS ////////////////////////////////////////////////////////
	//
	// [(constructor)](https://en.cppreference.com/w/cpp/container/vector/vector)
	// constructs the `vector`
	//
	// [(destructor)](https://en.cppreference.com/w/cpp/container/vector/~vector)
	// destructs the `vector`
	//
	// [operator=](https://en.cppreference.com/w/cpp/container/vector/operator%3D)
	// assigns values to the container
	//
	// [assign](https://en.cppreference.com/w/cpp/container/vector/assign)
	// assigns values to the container
	//
	// [get_allocator](https://en.cppreference.com/w/cpp/container/vector/get_allocator)
	// returns the associated allocator

	// ##### Element access ////////////////////////////////////////////////////
	//
	// [at](https://en.cppreference.com/w/cpp/container/vector/at)
	// access specified element with bounds checking
	//
	// [operator[]](https://en.cppreference.com/w/cpp/container/vector/operator_at)
	// access specified element
	//
	// [front](https://en.cppreference.com/w/cpp/container/vector/front)
	// access the first element
	//
	// [back](https://en.cppreference.com/w/cpp/container/vector/back)
	// access the last element
	//
	// [data](https://en.cppreference.com/w/cpp/container/vector/data)
	// direct access to the underlying array

	// ##### Iterators /////////////////////////////////////////////////////////
	//
	// [begin](https://en.cppreference.com/w/cpp/container/vector/begin)
	// returns an iterator to the beginning
	//
	// [end](https://en.cppreference.com/w/cpp/container/vector/end)
	// returns an iterator to the end
	//
	// [rbegin](https://en.cppreference.com/w/cpp/container/vector/rbegin)
	// returns a reverse iterator to the beginning
	//
	// [rend](https://en.cppreference.com/w/cpp/container/vector/rend)
	// returns a reverse iterator to the end
	//
	// ##### Capacity //////////////////////////////////////////////////////////
	//
	// [empty](https://en.cppreference.com/w/cpp/container/vector/empty)
	// checks whether the container is empty
	//
	// [size](https://en.cppreference.com/w/cpp/container/vector/size)
	// returns the number of elements
	//
	// [max_size](https://en.cppreference.com/w/cpp/container/vector/max_size)
	// returns the maximum possible number of elements
	//
	// [reserve](https://en.cppreference.com/w/cpp/container/vector/reserve)
	// reserves storage
	//
	// [capacity](https://en.cppreference.com/w/cpp/container/vector/capacity)
	// returns the number of elements that can be held in currently allocated storage

	// ##### Modifiers /////////////////////////////////////////////////////////
	//
	// [clear](https://en.cppreference.com/w/cpp/container/vector/clear)
	// clears the contents
	//
	// [insert](https://en.cppreference.com/w/cpp/container/vector/insert)
	// inserts elements
	//
	// [erase](https://en.cppreference.com/w/cpp/container/vector/erase)
	// erases elements
	//
	// [push_back](https://en.cppreference.com/w/cpp/container/vector/push_back)
	// adds an element to the end
	//
	// [pop_back](https://en.cppreference.com/w/cpp/container/vector/pop_back)
	// removes the last element
	//
	// [resize](https://en.cppreference.com/w/cpp/container/vector/resize)
	// changes the number of elements stored
	//
	// [swap](https://en.cppreference.com/w/cpp/container/vector/swap)
	// swaps the contents

	// NON-MEMBER FUNCTIONS ////////////////////////////////////////////////////
	//
	// [operator==](https://en.cppreference.com/w/cpp/container/vector/operator_cmp)
	// lexicographically compares the values in the vector (function template)
	//
	// operator!= (removed in C++20)
	//
	// operator< (removed in C++20)
	//
	// operator<= (removed in C++20)
	//
	// operator> (removed in C++20)
	//
	// operator>= (removed in C++20)
	//
	// [std::swap(std::vector)](https://en.cppreference.com/w/cpp/container/vector/swap2)
	// specializes the [std::swap](https://en.cppreference.com/w/cpp/algorithm/swap) algorithm  (function template)

};

}

#endif
