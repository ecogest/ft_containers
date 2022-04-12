/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:12:18 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/12 09:12:49 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "iterator.hpp"
#include <memory>
#include <functional> // std::less
#include "AVLTree.hpp"

namespace ft {

template<
	class Key,
	class T,
	class Compare = std::less<Key>, // check if allowed
	class Allocator = std::allocator<ft::pair<const Key, T> >
> class map {

public:
	// MEMBER TYPES ////////////////////////////////////////////////////////////
	typedef Key                                      key_type;
	typedef T                                    	 mapped_type;
	typedef ft::pair<const Key, T>              	 value_type;
	typedef std::size_t                          	 size_type;
	typedef std::ptrdiff_t                       	 difference_type;
	typedef Compare                              	 key_compare;
	typedef Allocator                            	 allocator_type;
	typedef value_type&                          	 reference;
	typedef const value_type&                    	 const_reference;
	typedef typename Allocator::pointer          	 pointer;
	typedef typename Allocator::const_pointer    	 const_pointer;

	class value_compare;
private:
	typedef AVLTree<value_type, value_compare, allocator_type>		tree_type;
	typedef typename tree_type::node_type							node_type;

public:
	typedef typename tree_type::iterator           	 iterator;               // LegacyBidirectionalIterator
	typedef typename tree_type::const_iterator     	 const_iterator;         // like mapIterator<const Key, const T>
	typedef ft::reverse_iterator<iterator>       	 reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> 	 const_reverse_iterator; // without ft:: it would use the typedef above

	//### MEMBER CLASSES ///////////////////////////////////////////////////////
	//
	//[value_compare](https://en.cppreference.com/w/cpp/container/map/value_compare "cpp/container/map/value compare")
	//compares objects of type `value_type`
	class value_compare {
		public:
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			typedef bool	result_type;
			bool operator()(first_argument_type const &a, first_argument_type const &b) const
			{ return comp(a.first, b.first); }
		protected:
			key_compare	comp;
			value_compare(key_compare c): comp(c) { }
			friend class map; // otherwise map cannot call the constructs above (protected)
	};


	//### MEMBER FUNCTIONS /////////////////////////////////////////////////////
	//
	//[(constructor)](https://en.cppreference.com/w/cpp/container/map/map "cpp/container/map/map")
	//constructs the `map`
	// 1) Constructs an empty container.
	// 2) Constructs the container with the contents of the range [first, last).
	// 3) Copy constructor. Constructs the container with the copy of the contents of other. (deep copy)
	map(): _key_comp(), _value_comp(_key_comp), _tree(_value_comp, Allocator()) { }                         // (1)

	explicit map( const Compare& comp, const Allocator& alloc = Allocator() )                               // (1)
		: _key_comp(comp), _value_comp(comp), _tree(_value_comp, alloc) { }

	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) // (2)
		: _key_comp(comp), _value_comp(comp), _tree(_value_comp, alloc) {
			insert(first, last);
		}

	map( const map& other )                                                                                 // (3)
		: _key_comp(other._key_comp), _value_comp(_key_comp), _tree(_value_comp, other.get_allocator()) {
			insert(other.begin(), other.end());
		}

	//[(destructor)](https://en.cppreference.com/w/cpp/container/map/~map "cpp/container/map/~map")
	//destructs the `map`
	~map() { }

	//[operator=](https://en.cppreference.com/w/cpp/container/map/operator%3D "cpp/container/map/operator=")
	//assigns values to the container
	map& operator=( const map& other ) {
		if (this == &other) return (*this); _tree = other._tree; return (*this);
	}

	//[get_allocator](https://en.cppreference.com/w/cpp/container/map/get_allocator "cpp/container/map/get allocator")
	//returns the associated allocator
	allocator_type get_allocator() const { return _tree.get_allocator(); }


	//##### ELEMENT ACCESS /////////////////////////////////////////////////////
	//
	//[at](https://en.cppreference.com/w/cpp/container/map/at "cpp/container/map/at")
	//access specified element with bounds checking
	T& at( const Key& key ) {
		iterator	it = find(key);
		if (it == end())
			throw std::out_of_range("map::at:  key not found"); // TODO: check if same error on linux
		else
			return (it->second);
	}
	const T& at( const Key& key ) const {
		const_iterator	it = find(key);
		if (it == end())
			throw std::out_of_range("map::at:  key not found");
		else
			return (it->second);
	}

	//[operator[]](https://en.cppreference.com/w/cpp/container/map/operator_at "cpp/container/map/operator at")
	//access or insert specified element
	T& operator[]( const Key& key ) {
		return insert(ft::make_pair(key, T())).first->second;
	}

	//##### ITERATORS //////////////////////////////////////////////////////////
	//
	//[begin](https://en.cppreference.com/w/cpp/container/map/begin "cpp/container/map/begin")
	//returns an iterator to the beginning
	iterator		begin()       { return (_tree.begin()); }
	const_iterator	begin() const { return (_tree.begin()); }
	//[end](https://en.cppreference.com/w/cpp/container/map/end "cpp/container/map/end")
	//returns an iterator to the end
	iterator		end()       { return (_tree.end()); }
	const_iterator	end() const { return (_tree.end()); }
	//[rbegin](https://en.cppreference.com/w/cpp/container/map/rbegin "cpp/container/map/rbegin")
	//returns a reverse iterator to the beginning
	reverse_iterator 		rbegin()       { return (reverse_iterator(end())); }
	const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
	//[rend](https://en.cppreference.com/w/cpp/container/map/rend "cpp/container/map/rend")
	//returns a reverse iterator to the end
	reverse_iterator		rend()       { return (reverse_iterator(begin())); }
	const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }



	//##### CAPACITY ///////////////////////////////////////////////////////////
	//
	//[empty](https://en.cppreference.com/w/cpp/container/map/empty "cpp/container/map/empty")
	//checks whether the container is empty
	bool empty() const { return _tree.empty(); }

	//[size](https://en.cppreference.com/w/cpp/container/map/size "cpp/container/map/size")
	//returns the number of elements
	size_type size() const { return _tree.size(); }

	//[max_size](https://en.cppreference.com/w/cpp/container/map/max_size "cpp/container/map/max size")
	//returns the maximum possible number of elements
	size_type max_size() const { return _tree.get_node_allocator().max_size(); }

	//##### MODIFIERS //////////////////////////////////////////////////////////
	//
	//[clear](https://en.cppreference.com/w/cpp/container/map/clear "cpp/container/map/clear")
	//clears the contents
	void clear() {
		_tree.clear();
	}

	//[insert](https://en.cppreference.com/w/cpp/container/map/insert "cpp/container/map/insert")
	//inserts elements or nodes (since C++17)
	// 1) insert value
	//   Returns a pair consisting of an iterator to the inserted element
	//   (or to the element that prevented the insertion)
	//   and a bool denoting whether the insertion took place.
	// 4) Inserts value in the position as close as possible to hint.
	//   Returns an iterator to the inserted element,
	//   or to the element that prevented the insertion.
	// 7) Inserts elements from range [first, last).
	ft::pair<iterator, bool> insert( const value_type& value ) { //(1)
		return (_tree.insert(value));
	}

	// iterator insert( iterator hint, const value_type& value ) { // (4) TODO:
	// }

	template< class InputIt >
	void insert( InputIt first, InputIt last ) { // (7)
		while (first != last)
			insert(*first++);
	}

	//[erase](https://en.cppreference.com/w/cpp/container/map/erase "cpp/container/map/erase")
	//erases elements
	// 1) Removes the element at pos
	// 2) Removes the elements in the range [first; last)
	// 3) Removes the element (if one exists) with the key equivalent to key.
	void erase( iterator pos ) { _tree.erase(pos); } // (1)
	void erase( iterator first, iterator last ) {    // (2)
		while (first != last)
			erase(first++);
	}
	size_type erase( const Key& key ) {              // (3)
		iterator it = find(key);
		if (it != end()) {
			erase(it);
			return (1);
		}
		else
			return (0);
	}

	//[swap](https://en.cppreference.com/w/cpp/container/map/swap "cpp/container/map/swap")
	//swaps the contents
	void swap( map& other ) {
		_tree.swap(other._tree); // do not std::swap(_tree, other._tree), otherwise it would do 2 deep copy...
		std::swap(_key_comp, other._key_comp);
		std::swap(_value_comp, other._value_comp);
	}


	//##### LOOKUP /////////////////////////////////////////////////////////////
	//
	//[count](https://en.cppreference.com/w/cpp/container/map/count "cpp/container/map/count")
	//returns the number of elements matching specific key (0 on 1)
	size_type count( const Key& key ) const { return (find(key) != end()); }

	//[find](https://en.cppreference.com/w/cpp/container/map/find "cpp/container/map/find")
	// Finds element with specific key
	// If no such element is found, past-the-end iterator is returned.
	iterator		find(const Key& key)       { return (_tree.find(key, _get_key, _key_comp)); }
	const_iterator	find(const Key& key) const { return (_tree.find(key, _get_key, _key_comp)); }

	//[equal_range](https://en.cppreference.com/w/cpp/container/map/equal_range "cpp/container/map/equal range")
	//returns range of elements matching a specific key
	ft::pair<iterator,iterator> equal_range( const Key& key ) {
		return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
	}
	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
		return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
	}

	//[lower_bound](https://en.cppreference.com/w/cpp/container/map/lower_bound "cpp/container/map/lower bound")
	//returns an iterator to the first element _not less_ than the given key
	iterator lower_bound( const Key& key ) {
		iterator it = begin();
		while (it != end() && _key_comp(it->first, key))
			it++;
		return (it);
	}
	const_iterator lower_bound( const Key& key ) const {
		const_iterator it = begin();
		while (it != end() && _key_comp(it->first, key))
			it++;
		return (it);
	}

	//[upper_bound](https://en.cppreference.com/w/cpp/container/map/upper_bound "cpp/container/map/upper bound")
	//returns an iterator to the first element _greater_ than the given key
	iterator upper_bound( const Key& key ) {
		iterator it = begin();
		while (it != end() && !_key_comp(key, it->first))
			it++;
		return (it);
	}
	const_iterator upper_bound( const Key& key ) const {
		const_iterator it = begin();
		while (it != end() && !_key_comp(key, it->first))
			it++;
		return (it);
	}


	//##### OBSERVERS //////////////////////////////////////////////////////////
	//
	//[key_comp](https://en.cppreference.com/w/cpp/container/map/key_comp "cpp/container/map/key comp")
	//returns the function that compares keys
	key_compare	key_comp() const { return _key_comp; }

	//[value_comp](https://en.cppreference.com/w/cpp/container/map/value_comp "cpp/container/map/value comp")
	//returns the function that compares keys in objects of type value_type
	value_compare	value_comp() const { return _value_comp; }

private:
	key_compare		_key_comp;
	value_compare	_value_comp;
	tree_type		_tree;

	static key_type const &_get_key(value_type const &v) { return (v.first); }

	// template <typename U>
	// void	_swap(U &a, U &b) { U tmp(a); a = b; b = tmp; }

};

 //### NON-MEMBER FUNCTIONS ////////////////////////////////////////////////////
 //
 //[operators](https://en.cppreference.com/w/cpp/container/map/operator_cmp "cpp/container/map/operator cmp")
 //lexicographically compares the values in the map

}
#endif
