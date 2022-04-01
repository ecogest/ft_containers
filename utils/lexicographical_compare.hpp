/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:15:28 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 15:38:40 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

//NOTE: tested in vector_test

namespace ft {

	//Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
	//1) Elements are compared using operator<.
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2 ) {
	while (first1 != last1 && first2 != last2) {
		if (*first1 == *first2) {
			first1++;
			first2++;
		}
		else return (*first1 < *first2);
	}
	return (first1 == last1 && first2 != last2);
}

	// 3) Elements are compared using the given binary comparison function comp.
	//  bool cmp(const Type1 &a, const Type2 &b); returns true if the first argument is less than the second.
template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp ) {
	while (first1 != last1 && first2 != last2) {
		if (comp(*first1, *first2))
			return (true);
		else if (comp(*first2, *first1))
			return (false);
		else {
			first1++;
			first2++;
		}
	}
	return (first1 == last1 && first2 != last2);
}

}

#endif
