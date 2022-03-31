/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:35:45 by mjacq             #+#    #+#             */
/*   Updated: 2022/03/31 16:38:52 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include <memory>

namespace ft {

// 	Satisfies: LegacyRandomAccessIterator and LegacyContiguousIterator to value_type
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
	vectorIterator(): _ptr(0)                                     { }
	vectorIterator(pointer ptr): _ptr(ptr)                        { }
	vectorIterator(vectorIterator const &it): _ptr(it.base())     { }
	vectorIterator	operator=(vectorIterator const &it)           { _ptr = it._ptr; }
	~vectorIterator()                                             { }
	// [LegacyRandomAccessIterator] < LegacyBidirectionalIterator
	vectorIterator	&operator+=(difference_type n)                { _ptr += n; return (*this); }
	vectorIterator	operator+(difference_type n) const            { vectorIterator tmp; tmp._ptr = _ptr + n; return (tmp); }
	vectorIterator	&operator-=(difference_type n)                { _ptr -= n; return (*this); }
	vectorIterator	operator-(difference_type n) const            { vectorIterator tmp; tmp._ptr = _ptr - n; return (tmp); }
	difference_type	operator-(vectorIterator const &a) const      { return (_ptr - a.base()); } // TODO: check
	reference		operator[](difference_type n) const           { return _ptr[n]; }
	bool			operator<(vectorIterator const &b) const      { return (b - *this > 0); }
	bool			operator>(vectorIterator const &b) const      { return (b - *this < 0); };
	bool			operator<=(vectorIterator const &b) const     { return (b - *this >= 0); }
	bool			operator>=(vectorIterator const &b) const     { return (b - *this <= 0); };
	// [LegacyBidirectionalIterator] < LegacyForwardIterator
	vectorIterator	&operator--()                                 { --_ptr; return (*this); }
	vectorIterator	operator--(int) { vectorIterator tmp; tmp._ptr = _ptr; _ptr--; return (tmp); }
	// [LegacyForwardIterator] < LegacyIterator, LegacyInputOperator, DefaultConstructible
	vectorIterator	operator++(int) { vectorIterator tmp; tmp._ptr = _ptr; _ptr++; return (tmp); }
	// [LegacyInputOperator] < (LegacyOperator), EquallyComparable
	bool			operator!=(vectorIterator const &rhs) const { return (_ptr != rhs.base()); }
	pointer			operator->() const                          { return (_ptr); }
	// [EquallyComparable]
	bool			operator==(vectorIterator const &rhs) const { return (_ptr == rhs.base()); }
	// [LegacyIterator]
	reference		operator*(void) const                       { return *_ptr; }
	vectorIterator	&operator++()                               { ++_ptr; return (*this); }
	// getter (same in system headers)
	value_type		*base(void) const                           { return _ptr; }
};

// [RandomAccessIterator]
template < class T >
vectorIterator<T>	operator+(
		typename vectorIterator<T>::difference_type n,
		vectorIterator<T> const &a) {
	return (a + n);
}

}
#endif
