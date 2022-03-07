/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:10:26 by mjacq             #+#    #+#             */
/*   Updated: 2022/03/07 17:36:37 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ref: https://en.cppreference.com/w/cpp/container/vector

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "reverse_iterator.hpp"
# include <iostream>
# include <stdexcept>
# include <sstream>

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

	// ITERATOR TYPES //////////////////////////////////////////////////////////
	// iterator	 LegacyRandomAccessIterator and LegacyContiguousIterator to value_type (until C++20)
	// const_iterator	 LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type (until C++20)
	// ref: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
	// ref: https://en.cppreference.com/w/cpp/named_req/ContiguousIterator
	template <class U>
	class _iterator {
		// TODO:
	};

	typedef _iterator<T> iterator;
	typedef _iterator<const T> const_iterator;

	// reverse_iterator	std::reverse_iterator<iterator>
	typedef ft::reverse_iterator<iterator> reverse_iterator;

	// const_reverse_iterator	std::reverse_iterator<const_iterator>
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// MEMBER FUNCTIONS ////////////////////////////////////////////////////////
	//
	// [(constructor)](https://en.cppreference.com/w/cpp/container/vector/vector)
	// constructs the `vector`
	// 1) Default constructor. Constructs an empty container with a default-constructed allocator.
	vector():
		_array(0),
		_allocator(allocator_type()),
		_size(0)
	{ }

	// 2) Constructs an empty container with the given allocator alloc.
	// explicit vector(const Allocator& alloc); // (until C++17)
	explicit vector(const Allocator& alloc):
		// _array(alloc.allocate(0)), // NO! we want our copy _allocator
		_array(0),
		_allocator(alloc),
		_size(0)
	{
		// _array = _allocator.allocate(0); // actually null pointer seems fine
	}

	// 3) Constructs the container with count copies of elements with value value.
	// (until C++11)
	explicit vector(size_type count,
				 const T& value = T(),
				 const Allocator& alloc = Allocator()
		):
		_allocator(alloc),
		_size(count)
	{
		_array = _allocator.allocate(count); // allocate with _allocator and not alloc !
		for (size_type i = 0; i < count; i++)
			_allocator.construct(_array + i, value);
	}

	// 5) Constructs the container with the contents of the range [first, last).
	// This constructor has the same effect as:
	// vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
	// if InputIt is an integral type. // TODO:
	template< class InputIt >
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()); // (until C++20)

	// 6) Copy constructor. Constructs the container with the copy of the contents of other.
	// (until C++20)
	vector(const vector& other):
		_allocator(other.get_allocator()),
		_size(other.size())
	{
		_array = _allocator.allocate(_size);
		for (size_t i = 0; i < _size; i++)
			_allocator.construct(_array + i, other[i]); // could use other.at(i) as well
			// _array[i] = other[i]; // NO! otherwise we have valgrind errors
	}

	// [(destructor)](https://en.cppreference.com/w/cpp/container/vector/~vector)
	// destructs the `vector`
	~vector() {
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_array + i);
		_allocator.deallocate(_array, _size);
	}

	// [operator=](https://en.cppreference.com/w/cpp/container/vector/operator%3D)
	// assigns values to the container
	//
	// [assign](https://en.cppreference.com/w/cpp/container/vector/assign)
	// assigns values to the container
	//
	// [get_allocator](https://en.cppreference.com/w/cpp/container/vector/get_allocator)
	// returns the associated allocator
	allocator_type get_allocator() const {
		return (_allocator);
	}

	// ##### Element access ////////////////////////////////////////////////////
	//
	// [at](https://en.cppreference.com/w/cpp/container/vector/at)
	// access specified element with bounds checking
	// out_of_range exception: vector::_M_range_check: __n (which is 3) >= this->size() (which is 3)
	reference at( size_type pos ) {
		if (pos < _size)
			return (_array[pos]);
		else
		{
			std::ostringstream	error_stream;
			error_stream << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << _size << ")";
			throw (std::out_of_range(error_stream.str()));
		}
	}

	const_reference at( size_type pos ) const {
		if (pos < _size)
			return (_array[pos]);
		else
		{
			std::ostringstream	error_stream;
			error_stream << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << _size << ")";
			throw (std::out_of_range(error_stream.str()));
		}
	}

	// [operator[]](https://en.cppreference.com/w/cpp/container/vector/operator_at)
	// access specified element (no bound checking)
	reference operator[]( size_type pos ) {
		return (_array[pos]);
	}
	const_reference operator[]( size_type pos ) const {
		return (_array[pos]);
	}

	// [front](https://en.cppreference.com/w/cpp/container/vector/front)
	// access the first element
	reference front() {
		return (_array[0]);
	}
	const_reference front() const {
		return (_array[0]);
	}
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
	size_type size() const {
		return (_size);
	}

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

private:
	value_type		*_array; // The elements are stored contiguously.
	allocator_type	_allocator;
	size_type		_size;
};

// NON-MEMBER FUNCTIONS ////////////////////////////////////////////////////////
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

}

#endif
