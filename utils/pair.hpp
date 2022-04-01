/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:16:16 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 16:10:30 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

template <class T1, class T2>
class pair {
public:
	// Member types
	typedef T1	first_type;
	typedef T2	second_type;

	// Member objects (public)
	first_type	first;
	second_type	second;

	//	### Member functions
	//[(constructor)](https://en.cppreference.com/w/cpp/utility/pair/pair "cpp/utility/pair/pair")
	//constructs new pair

	//[operator=](https://en.cppreference.com/w/cpp/utility/pair/operator%3D "cpp/utility/pair/operator=")
	//assigns the contents
};

//### Non-member functions
//[make_pair](https://en.cppreference.com/w/cpp/utility/pair/make_pair "cpp/utility/pair/make pair")
//creates a `pair` object of type, defined by the argument types
//
//[operators](https://en.cppreference.com/w/cpp/utility/pair/operator_cmp "cpp/utility/pair/operator cmp")
//
//lexicographically compares the values in the pair
//(function template)

}

#endif
