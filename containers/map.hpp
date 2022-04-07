/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:12:18 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/07 14:06:02 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "iterator.hpp"
#include <memory>
#include <functional> // std::less

namespace ft {

template <class Key, class T>
class mapIterator { // should be a LegacyBidirectionalIterator
public:
};

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
	typedef std::size_t                          	 size_type; // check type
	typedef std::ptrdiff_t                       	 difference_type; // check type
	typedef Compare                              	 key_compare;
	typedef Allocator                            	 allocator_type;
	typedef value_type&                          	 reference;
	typedef const value_type&                    	 const_reference;
	typedef typename Allocator::pointer          	 pointer;
	typedef typename Allocator::const_pointer    	 const_pointer;
	typedef mapIterator<Key, T>                  	 iterator; // not sure
	typedef mapIterator<const Key, const T>      	 const_iterator; // not sure
	typedef ft::reverse_iterator<iterator>       	 reverse_iterator; // think of the ft:: part or the linter won't like
	typedef ft::reverse_iterator<const_iterator> 	 const_reverse_iterator;

	//### Member classes
	//
	//[value_compare](https://en.cppreference.com/w/cpp/container/map/value_compare "cpp/container/map/value compare")
	//compares objects of type `value_type`
	class value_compare {
		public:
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			typedef bool	result_type;
			bool operator()(first_argument_type const &a, first_argument_type const &b) const { return comp(a.first, b.first); }
		protected:
			key_compare	comp;
			value_compare(key_compare c): comp(c) { }
			friend class map; // otherwise map cannot call the constructs above (protected)
	};


	//### Member functions
	//
	//[(constructor)](https://en.cppreference.com/w/cpp/container/map/map "cpp/container/map/map")
	//constructs the `map`
	// 1)
	map(): _key_comp(), _value_comp(_key_comp), _alloc(Allocator()) { }
	explicit map( const Compare& comp, const Allocator& alloc = Allocator() ):
		_key_comp(comp), _value_comp(comp), _alloc(alloc) { }

	//[(destructor)](https://en.cppreference.com/w/cpp/container/map/~map "cpp/container/map/~map")
	//destructs the `map`

	//[operator=](https://en.cppreference.com/w/cpp/container/map/operator%3D "cpp/container/map/operator=")
	//assigns values to the container

	//[get_allocator](https://en.cppreference.com/w/cpp/container/map/get_allocator "cpp/container/map/get allocator")
	//returns the associated allocator


	//##### Element access
	//
	//[at](https://en.cppreference.com/w/cpp/container/map/at "cpp/container/map/at")
	//access specified element with bounds checking

	//[operator[]](https://en.cppreference.com/w/cpp/container/map/operator_at "cpp/container/map/operator at")
	//access or insert specified element


	//##### Iterators
	//
	//[begin](https://en.cppreference.com/w/cpp/container/map/begin "cpp/container/map/begin")
	//returns an iterator to the beginning

	//[end](https://en.cppreference.com/w/cpp/container/map/end "cpp/container/map/end")
	//returns an iterator to the end

	//[rbegin](https://en.cppreference.com/w/cpp/container/map/rbegin "cpp/container/map/rbegin")
	//returns a reverse iterator to the beginning

	//[rend](https://en.cppreference.com/w/cpp/container/map/rend "cpp/container/map/rend")
	//returns a reverse iterator to the end


	//##### Capacity
	//
	//[empty](https://en.cppreference.com/w/cpp/container/map/empty "cpp/container/map/empty")
	//checks whether the container is empty

	//[size](https://en.cppreference.com/w/cpp/container/map/size "cpp/container/map/size")
	//returns the number of elements

	//[max_size](https://en.cppreference.com/w/cpp/container/map/max_size "cpp/container/map/max size")
	//returns the maximum possible number of elements


	//##### Modifiers
	//
	//[clear](https://en.cppreference.com/w/cpp/container/map/clear "cpp/container/map/clear")
	//clears the contents

	//[insert](https://en.cppreference.com/w/cpp/container/map/insert "cpp/container/map/insert")
	//inserts elements or nodes (since C++17)

	//[erase](https://en.cppreference.com/w/cpp/container/map/erase "cpp/container/map/erase")
	//erases elements

	//[swap](https://en.cppreference.com/w/cpp/container/map/swap "cpp/container/map/swap")
	//swaps the contents


	//##### Lookup
	//
	//[count](https://en.cppreference.com/w/cpp/container/map/count "cpp/container/map/count")
	//returns the number of elements matching specific key

	//[find](https://en.cppreference.com/w/cpp/container/map/find "cpp/container/map/find")
	//finds element with specific key

	//[equal_range](https://en.cppreference.com/w/cpp/container/map/equal_range "cpp/container/map/equal range")
	//returns range of elements matching a specific key

	//[lower_bound](https://en.cppreference.com/w/cpp/container/map/lower_bound "cpp/container/map/lower bound")
	//returns an iterator to the first element _not less_ than the given key

	//[upper_bound](https://en.cppreference.com/w/cpp/container/map/upper_bound "cpp/container/map/upper bound")
	//returns an iterator to the first element _greater_ than the given key


	//##### Observers
	//
	//[key_comp](https://en.cppreference.com/w/cpp/container/map/key_comp "cpp/container/map/key comp")
	//returns the function that compares keys
	key_compare	key_comp() const { return _key_comp; }

	//[value_comp](https://en.cppreference.com/w/cpp/container/map/value_comp "cpp/container/map/value comp")
	//returns the function that compares keys in objects of type value_type
	value_compare	value_comp() const { return _value_comp; }

private:
	key_compare	_key_comp;
	value_compare	_value_comp;
	allocator_type	_alloc;

};

 //### Non-member functions
 //
 //[operators](https://en.cppreference.com/w/cpp/container/map/operator_cmp "cpp/container/map/operator cmp")
 //lexicographically compares the values in the map

}
#endif
