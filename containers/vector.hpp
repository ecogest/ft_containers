/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:10:26 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/12 12:09:51 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ref: https://en.cppreference.com/w/cpp/container/vector

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <memory>
# include "iterator.hpp"
# include "vectorIterator.hpp"
# include "lexicographical_compare.hpp"
# include "type_traits.hpp"
# include <iostream>
# include <stdexcept>
# include <sstream>
# include <cstring>
// # include <vector>
// # include <iterator> // check __normal_iterator in it

namespace ft {

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

	typedef vectorIterator<T>                       iterator;
	// Another option to enable converstion from iterator to const iterator
	// is to use a template <bool isconst> class vectorIterator
	// https://quuxplusone.github.io/blog/2018/12/01/const-iterator-antipatterns/
	typedef vectorIterator<const T>                 const_iterator;
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
	// 1) Replaces the contents with count copies of value value
	void assign( size_type count, const T& value ) {
		clear();
		insert(begin(), count, value);
	}
	// 2) Replaces the contents with copies of those in the range [first, last).
	template< class InputIt >
	void assign( InputIt first, InputIt last ) {
		clear();
		insert(begin(), first, last);
	}

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
	const_iterator begin() const { return (const_iterator(_array)); };
	//
	// [end](https://en.cppreference.com/w/cpp/container/vector/end)
	// returns an iterator to the end (actually past the end)
	iterator end() { return (iterator(_array + _size)); }
	const_iterator end() const { return (const_iterator(_array + _size)); }

	// [rbegin](https://en.cppreference.com/w/cpp/container/vector/rbegin)
	// returns a reverse iterator to the beginning
	reverse_iterator rbegin() {
		return (reverse_iterator(end()));
	}
	const_reverse_iterator rbegin() const {
		return (const_reverse_iterator(end()));
	}
	// [rend](https://en.cppreference.com/w/cpp/container/vector/rend)
	// returns a reverse iterator to the end
	reverse_iterator rend() {
		return (reverse_iterator(begin()));
	}
	const_reverse_iterator rend() const {
		return (const_reverse_iterator(begin()));
	}
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
			_allocator.destroy(_array + i);
		_size = 0;
	}

	// [insert](https://en.cppreference.com/w/cpp/container/vector/insert)
	// inserts elements
	// 1) inserts value before pos. Return iterator pointing to the inserted value
	iterator insert( iterator pos, const T& value ) {
		size_t	index = pos - iterator(_array);  // implicit casting from difference_type

		insert(pos, 1, value);
		return (iterator(_array + index));
	}
	// 3) inserts count copies of the value before pos.
	void insert( iterator pos, size_type count, const T& value ) {
		size_t	index = pos - iterator(_array);  // implicit casting from difference_type

		if (_capacity < _size + count)
			reserve(_size + count);
		_size += count;
		for(size_t i = _size - 1; i >= index + count; i--) {
			_allocator.construct(_array + i, _array[i - count]);
			_allocator.destroy(&_array[i - count]);
		}
		for (size_t i = 0; i < count; i++)
			_allocator.construct(_array + index + i, value);
	}
	// 4) inserts elements from range [first, last) before pos.
	// note: we do not want this template to overshadow the one above
	// simplest way to ensure that is to make sure the InputIt is not an integral
	template< class InputIt >
	typename ft::enable_if<!ft::is_integral<InputIt>::value >::type insert( iterator pos, InputIt first, InputIt last ) {
		// size_t	count = last - first; // not necessary implemented by a basic InputIt
		size_t	count = 0;
		for (InputIt it = first; it != last; it++)
			count++;
		size_t	index = pos - iterator(_array);  // implicit casting from difference_type

		if (_capacity < _size + count)
			reserve(_size + count);  // some implementations reserve more, OS dependant, no such behaviour required in the doc
		_size += count;
		for(size_t i = _size - 1; i >= index + count; i--) {
			_allocator.construct(_array + i, _array[i - count]);
			_allocator.destroy(&_array[i - count]);
		}
		for (size_t i = 0; i < count; i++, first++)
			_allocator.construct(_array + index + i, *first);
	}

	// [erase](https://en.cppreference.com/w/cpp/container/vector/erase)
	// erases elements. returns the iterator following the last removed element
	// 1) Removes the element at pos.
	iterator erase( iterator pos ) {
		return (erase(pos, pos + 1));
	}
	// 2) Removes the elements in the range [first, last).
	iterator erase( iterator first, iterator last ) {
		size_type start = first - this->begin();
		size_type end = last - this->begin();
		if (end == start)
			return (first);
		for (size_type i = start; i < end; i++) {
			_allocator.destroy(_array + i);
		}
		for (size_type i = 0; end + i < _size; i++) {
			_allocator.construct(_array + start + i, _array[end + i]);
		}
		_size -= (end - start);
		return (first);
	}

	// [push_back](https://en.cppreference.com/w/cpp/container/vector/push_back)
	// adds an element to the end
	void push_back( const T& value ) {
		if (_size <= _capacity)
			reserve(_size + 1);  // some implementations reserve more, OS dependant, no such behaviour required in the doc
		_allocator.construct(_array + _size, value);
		_size++;
	}
	// [pop_back](https://en.cppreference.com/w/cpp/container/vector/pop_back)
	// removes the last element
	void pop_back() {
		if (_size) {
			_allocator.destroy(_array + _size -1);
			_size--;
		}
	}
	// [resize](https://en.cppreference.com/w/cpp/container/vector/resize)
	// changes the number of elements stored.
	// if the current size is greater than count, the container is reduced to its first count elements.
	// If the current size is less than count, additional copies of value are appended.
	void resize( size_type count, T value = T() ) {
		if (count == _size)
			return ;
		else if (count > _size) {
			if (count > _capacity)
				reserve(count);
			for (size_t i = _size; i < count; i++)
				_allocator.construct(_array + i, value);
		}
		else {
			for (size_t i = count; i < _size; i++)
				_allocator.destroy(_array + i);
		}
		_size = count;
	}
	// [swap](https://en.cppreference.com/w/cpp/container/vector/swap)
	// swaps the contents
	void swap( vector& other ) { // TODO: use ft:swap and check iterators !
		std::swap(_array, other._array);  // allowed, defined in <move.h>, standard library, not the container method
		std::swap(_allocator, other._allocator);
		std::swap(_capacity, other._capacity);
		std::swap(_size, other._size);
	}

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
template< class T, class Alloc >
bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs[i] != rhs[i])
			return (false);
	return (true);
}
// operator!=
template< class T, class Alloc >
bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )  {
	return (!(lhs == rhs));
}
// operator<
template< class T, class Alloc >
bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {
	return (ft::lexicographical_compare(
				lhs.begin(),
				lhs.end(),
				rhs.begin(),
				rhs.end()
				));
}
// operator<=
template< class T, class Alloc >
bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {
	return (operator==(lhs, rhs) || operator<(lhs, rhs));
}
// operator>
template< class T, class Alloc >
bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {
	return (operator>=(lhs, rhs) && operator!=(lhs, rhs));
}
// operator>=
template< class T, class Alloc >
bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {
	return (!operator<(lhs, rhs));
}

// [std::swap(std::vector)](https://en.cppreference.com/w/cpp/container/vector/swap2)
// specializes the [std::swap](https://en.cppreference.com/w/cpp/algorithm/swap) algorithm  (function template)
template< class T, class Alloc >
void swap(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) { lhs.swap(rhs); }

} // ft
#endif
// vim: fdm=marker
