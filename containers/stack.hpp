/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:13:08 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/16 11:40:58 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>

namespace ft {

template<class T, class Container = std::deque<T> >
class stack {
public:
	// ### Member types
	//
	typedef 			Container					container_type;
	typedef typename	Container::value_type		value_type;
	typedef typename	Container::size_type		size_type;
	typedef typename	Container::reference		reference;
	typedef typename	Container::const_reference	const_reference;


	// ### Member functions
	//
	// [(constructor)](https://en.cppreference.com/w/cpp/container/stack/stack "cpp/container/stack/stack")
	// constructs the `stack`
	// 2) Copy-constructs the underlying container c with the contents of cont.
	// 4) Copy constructor. The adaptor is copy-constructed with the contents of other.c.
	explicit stack(const Container& cont = Container()) : c(cont)    { } // (2)
	stack( const stack& other )                         : c(other.c) { } // (4)

	// [(destructor)](https://en.cppreference.com/w/cpp/container/stack/~stack "cpp/container/stack/~stack")
	// destructs the `stack`
	~stack() { }

	// [operator=](https://en.cppreference.com/w/cpp/container/stack/operator%3D "cpp/container/stack/operator=")
	// assigns values to the container adaptor
	// IMPLICITLY DECLARED
	// stack& operator=( const stack& other ) { c = other.c; }


	// ##### Element access
	//
	// [top](https://en.cppreference.com/w/cpp/container/stack/top "cpp/container/stack/top")
	// accesses the top element
	reference top()             { return (c.back()); }
	const_reference top() const { return (c.back()); }


	// ##### Capacity
	// [empty](https://en.cppreference.com/w/cpp/container/stack/empty "cpp/container/stack/empty")
	// checks whether the underlying container is empty
	bool empty() const { return (c.empty()); }

	// [size](https://en.cppreference.com/w/cpp/container/stack/size "cpp/container/stack/size")
	// returns the number of elements
	size_type size() const { return (c.size()); }


	// ##### Modifiers
	//
	// [push](https://en.cppreference.com/w/cpp/container/stack/push "cpp/container/stack/push")
	// inserts element at the top
	void push( const value_type& value ) { c.push_back(value); }

	// [pop](https://en.cppreference.com/w/cpp/container/stack/pop "cpp/container/stack/pop")
	// removes the top element
	void pop() { c.pop_back(); }


	// ### Member objects
	//
	// Container c
	// the underlying container
protected:
	container_type	c;

	// ### Operators
	// friend is needed to acces protected attribute
	friend bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.c == rhs.c);
	}
	friend bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.c != rhs.c);
	}
	friend bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.c < rhs.c);
	}
	friend bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.c <= rhs.c);
	}
	friend bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.c > rhs.c);
	}
	friend bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.c >= rhs.c);
	}
};

} // ft

#endif
