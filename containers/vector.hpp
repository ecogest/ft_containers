/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:10:26 by mjacq             #+#    #+#             */
/*   Updated: 2022/03/30 11:34:24 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ref: https://en.cppreference.com/w/cpp/container/vector

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <memory>
# include "iterator.hpp"
# include <iostream>
# include <stdexcept>
# include <sstream>

namespace ft {

	// 	vectorIterator should be a random access iterator to value_type
	//  In the headers, it is a typedef to __gnu_cxx::__normal_iterator
template < class T >
class vectorIterator // public ft::iterator<T>  // TODO: check if we can use it
{
public:
	typedef typename std::ptrdiff_t                  difference_type; // TODO: see if possible https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
	typedef T                                        value_type;
	typedef value_type*                              pointer;
	typedef value_type&                              reference;
	typedef typename std::random_access_iterator_tag iterator_category;  // TODO: check if ft::random_access_iterator_tag is OK
private:
	pointer	_ptr;
public:
	// [RandomAccessIterator]
	vectorIterator(): _ptr(0) { }
	vectorIterator(pointer ptr): _ptr(ptr) { }  // useful ?
	vectorIterator(vectorIterator const &it): _ptr(it.base()) { }
	~vectorIterator() { }
	reference		operator[](size_t i) { return _ptr[i]; }
	reference		operator*(void) { return *_ptr; }
	vectorIterator	operator++(int) { _ptr++; return (vectorIterator(_ptr - 1)); }
	bool			operator!=(vectorIterator const &rhs) const { return (_ptr != rhs.base()); }
	value_type		*base(void) const { return _ptr; }
};

template < class T, class Allocator = std::allocator<T> >
class vector {
public:

	// MEMBER TYPES ////////////////////////////////////////////////////////////
	//https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator

	typedef T                                    value_type;
	typedef Allocator                            allocator_type;
	typedef std::size_t                          size_type;       // Unsigned integer type (usually std::size_t)
	typedef std::ptrdiff_t                       difference_type; // Signed integer type (usually std::ptrdiff_t)
	typedef value_type&                          reference;
	typedef const value_type&                    const_reference;
	typedef typename Allocator::pointer          pointer;         // (until C++11)
	typedef typename Allocator::const_pointer    const_pointer;   // (until C++11)

	// ITERATOR TYPES //////////////////////////////////////////////////////////
	// iterator	 LegacyRandomAccessIterator and LegacyContiguousIterator to value_type (until C++20)
	// const_iterator	 LegacyRandomAccessIterator and LegacyContiguousIterator to const value_type (until C++20)
	// ref: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
	// ref: https://en.cppreference.com/w/cpp/named_req/ContiguousIterator
	// template < class U >
	// class _iterator {
	// public:
	// 	typedef typename vector<U>::difference_type      difference_type;
	// 	typedef U                                        value_type;
	// 	typedef value_type*                              pointer;
	// 	typedef value_type&                              reference;
	// 	typedef typename std::random_access_iterator_tag iterator_category;  // TODO: check if ft::random_access_iterator_tag is OK
	// private:
	// 	pointer	_ptr;
	// public:
	// };

	typedef vectorIterator<T>                            iterator;
	typedef vectorIterator<const T>                      const_iterator;
	typedef ft::reverse_iterator<iterator>          reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

	// MEMBER FUNCTIONS ////////////////////////////////////////////////////////
	//
	// [(constructor)](https://en.cppreference.com/w/cpp/container/vector/vector)
	// constructs the `vector`
	// 1) Default constructor. Constructs an empty container with a default-constructed allocator.
	vector():
		_array(0),
		_allocator(allocator_type()),
		_capacity(0),
		_size(0)
	{ }

	// 2) Constructs an empty container with the given allocator alloc.
	// explicit vector(const Allocator& alloc); // (until C++17)
	explicit vector(const Allocator& alloc):
		// _array(alloc.allocate(0)), // NO! we want our copy _allocator
		_array(0),
		_allocator(alloc),
		_capacity(0),
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
		_capacity(count),
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
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()):
		_allocator(alloc),
		_size(0)
	{
		for (InputIt it = first; it != last; it++)
			_size++;
		_capacity = _size;
		_array = _allocator.allocate(_size);  // alloc.allocate(_size) would be an error (alloc is const)
		size_t	i = 0;
		for (InputIt it = first; it != last; it++, i++) {
			_allocator.construct(_array + i, *it);
		}
	}

	// 6) Copy constructor. Constructs the container with the copy of the contents of other.
	// (until C++20)
	vector(const vector& other):
		_allocator(other.get_allocator()),
		_capacity(other.capacity()),
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
	vector& operator=(const vector& other) {
		if (this == &other)
			return (*this);
		this->clear();
		this->reserve(other.capacity());
		_size = other.size();
		for (size_t i = 0; i < _size; i++)
			_allocator.construct(_array + i, other[i]);
		return (*this);
	}

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
			throw (std::out_of_range(out_of_range_string(pos)));
	}
	const_reference at( size_type pos ) const {
		if (pos < _size)
			return (_array[pos]);
		else
			throw (std::out_of_range(out_of_range_string(pos)));
	}
private:
	std::string	out_of_range_string(size_type pos) const {
#ifdef __APPLE__
		(void)pos;
		return ("vector");
#else
		std::ostringstream	error_stream;
		error_stream << "vector::_M_range_check: __n (which is " << pos;
		error_stream << ") >= this->size() (which is " << _size << ")";
		return (error_stream.str());
#endif
	}

public:
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

	// [back](https://en.cppreference.com/w/cpp/container/vector/back)
	// access the last element
	reference back() {
		return (_array[_size - 1]);
	}
	const_reference back() const {
		return (_array[_size - 1]);
	}

	// [data](https://en.cppreference.com/w/cpp/container/vector/data)
	// direct access to the underlying array
	T* data() {
		return (_array);
	}
	const T* data() const {
		return (_array);
	}

	// ##### Iterators /////////////////////////////////////////////////////////
	//
	// [begin](https://en.cppreference.com/w/cpp/container/vector/begin)
	// returns an iterator to the beginning
	iterator begin() { return (iterator(_array)); }
	const_iterator begin() const { return (iterator(_array)); };
	//
	// [end](https://en.cppreference.com/w/cpp/container/vector/end)
	// returns an iterator to the end (actually past the end)
	iterator end() { return (iterator(_array + _size)); }
	const_iterator end() const { return (iterator(_array + _size));};

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
	bool empty() const {
		return (_size == 0);
	}

	// [size](https://en.cppreference.com/w/cpp/container/vector/size)
	// returns the number of elements
	size_type size() const {
		return (_size);
	}

	// [max_size](https://en.cppreference.com/w/cpp/container/vector/max_size)
	// returns the maximum possible number of elements
	size_type max_size() const {
		return (_allocator.max_size());
		// for some reason the following returns half the max size (probably a matter of sign)
		// return (std::numeric_limits<difference_type>::max());
	}

	// [reserve](https://en.cppreference.com/w/cpp/container/vector/reserve)
	// reserves storage if new_cap > capacity()
	void reserve(size_type new_cap) {
		if (new_cap > max_size())
#ifdef __APPLE__
			throw (std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
#else
			throw (std::length_error("vector::reserve"));
#endif
		if (new_cap > _capacity) {
			value_type	*new_array;

			new_array = _allocator.allocate(new_cap);
			for (size_type i = 0; i < _size; i++) {
				_allocator.construct(new_array + i, _array[i]);
				_allocator.destroy(_array + i);
			}
			_allocator.deallocate(_array, _capacity);
			_capacity = new_cap;
			_array = new_array;
		}
	}

	// [capacity](https://en.cppreference.com/w/cpp/container/vector/capacity)
	// returns the number of elements that can be held in currently allocated storage
	size_type capacity() const {
		return (_capacity);
	}

	// ##### Modifiers /////////////////////////////////////////////////////////
	//
	// [clear](https://en.cppreference.com/w/cpp/container/vector/clear)
	// clears the contents (erase all, size = 0, capacity unchanged)
	void clear() {
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_array + 1);
		_size = 0;
	}

	// [insert](https://en.cppreference.com/w/cpp/container/vector/insert)
	// inserts elements
	// 1) inserts value before pos. Return iterator pointing to the inserted value
	// iterator insert( iterator pos, const T& value );
	// 3) inserts count copies of the value before pos.
	// void insert( iterator pos, size_type count, const T& value );
	// 4) inserts elements from range [first, last) before pos.
	// template< class InputIt >
	// void insert( iterator pos, InputIt first, InputIt last );

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
	size_type		_capacity;
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
// vim: fdm=marker
