/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:26:53 by mjacq             #+#    #+#             */
/*   Updated: 2022/03/07 11:18:46 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>

int	main(void) {
	// VECTORS /////////////////////////////////////////////////////////////////
	std::vector<int>	v;
	ft::vector<int>		v2;

	std::cout << v.capacity() << std::endl;
	std::vector<int>::value_type	i = 1;
	ft::vector<int>::value_type	j = i;
	std::cout << j << std::endl;

	return (0);
}
