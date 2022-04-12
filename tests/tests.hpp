/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:20:04 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/12 16:45:31 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

# include <iostream>
#include "pair.hpp"
#include "AVLTree.hpp"
#include "vector.hpp"
#include "map.hpp"

void	test_vector(void);
void	test_utils(void);

namespace std { // namespace std would work too, but global scope would not 🤷
template <class Key, class Value>
std::ostream	&operator<<(std::ostream &os, ft::pair<Key, Value> const &p) {
	os << "(" << p.first << ", " << p.second << ")";
	return (os);
}
template <class Key, class Value>
std::ostream	&operator<<(std::ostream &os, std::pair<Key, Value> const &p) {
	os << "(" << p.first << ", " << p.second << ")";
	return (os);
}
}

void	test_avl(void);
void	test_map(void);
void	test_stack(void);
void	subject_tests(int, const char **);

#endif
