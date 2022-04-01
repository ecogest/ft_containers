/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:33 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 15:05:04 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enable_if.hpp"
#include <iostream>

#define DEBUG_TEST true

ft::enable_if<DEBUG_TEST>::type	echo_debug(void) {
	std::cout << "DEBUG" << std::endl;
}

static void	test_enable_if() {
	echo_debug();
}

static void test_equal() {
}

static void test_pair() {
}

void	test_utils(void) {
	test_enable_if();
	test_equal();
	test_pair();
}
