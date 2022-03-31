/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:15:28 by mjacq             #+#    #+#             */
/*   Updated: 2022/03/31 13:22:00 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
# define EQUAL_HPP

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
		else if (*first1 < *first2)
			return (true);
		else
			return (false);
	}
	if (first1 == last1 && first2 != last2)
		return (true);
	return (false);
}

}
	// 3) Elements are compared using the given binary comparison function comp.
template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp );

#endif
