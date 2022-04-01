/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:12:18 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 17:48:28 by mjacq            ###   ########.fr       */
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
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
> class map {
public:
	// MEMBER TYPES ////////////////////////////////////////////////////////////
	 typedef T                                    	 mapped_type;
	 typedef std::pair<const Key, T>              	 value_type;
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
};

}
#endif
