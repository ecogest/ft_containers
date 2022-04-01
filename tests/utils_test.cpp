/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:33 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 15:36:24 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type_traits.hpp"
#include <iostream>

#define DEBUG_TEST true

static ft::enable_if<DEBUG_TEST>::type	echo_debug(void) {
	std::cout << "DEBUG" << std::endl;
}

static void	test_enable_if() {
	echo_debug();
}

static void test_is_integral() {
	std::cout << std::boolalpha;
	std::cout << ft::is_integral<bool>::value << std::endl;
	std::cout << ft::is_integral<long long>::value << std::endl;
	std::cout << !ft::is_integral<float>::value << std::endl;
	std::cout << std::noboolalpha;
}


static void test_equal() {
}

static void test_pair() {
}

void	test_utils(void) {
	test_enable_if();
	test_is_integral();
	test_equal();
	test_pair();
}
