/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:20:04 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/10 11:01:01 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

# include <iostream>
#include "pair.hpp"
#include "AVLTree.hpp"
#include "map.hpp"

void	test_vector(void);
void	test_utils(void);

namespace ft { // namespace std would work too, but global scope would not 🤷
template <class Key, class Value>
std::ostream	&operator<<(std::ostream &os, ft::pair<Key, Value> const &p) {
	os << "(" << p.first << ", " << p.second << ")";
	return (os);
}
}

void	test_avl(void);
void	test_map(void);

#endif
