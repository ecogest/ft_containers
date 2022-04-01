/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:33 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/01 17:20:46 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type_traits.hpp"
#include "pair.hpp"
#include <utility> // pair
#include <iostream>

#define DEBUG_TEST true

static ft::enable_if<DEBUG_TEST>::type	echo_debug(void) {
	std::cout << "DEBUG" << std::endl;
}

static void	test_enable_if() {
	echo_debug();
}

static void test_is_integral() {
	std::cout << "=== IS_INTEGRAL ===" << std::boolalpha << std::endl;
	std::cout << ft::is_integral<bool>::value << std::endl;
	std::cout << ft::is_integral<long long>::value << std::endl;
	std::cout << !ft::is_integral<float>::value << std::endl;
	std::cout << !ft::is_integral<std::string>::value << std::endl;
	std::cout << std::noboolalpha;
}

static void test_pair() {
	{
		// 1) Default constructor. Value-initializes both elements of the pair, first and second.
		NS::pair<float, const char *> p;
		p.first = 42.42; p.second = "fortytwo";
		std::cout << p.first << " " << p.second << std::endl;

		// 2) Initializes first with x and second with y.
		NS::pair<float, const char *> pp(42.42, "fortytwo");
		std::cout << pp.first << " " << pp.second << std::endl;

		// 5) Initializes first with p.first and second with p.second.
		NS::pair<int, std::string> l(p);
		std::cout << l.first << " " << l.second << std::endl;

		// 9) Copy constructor is implicitly declared (until C++11) defaulted, and is constexpr
		NS::pair<float, const char *> q(p);
		std::cout << q.first << " " << q.second << std::endl;
	}
	{
		// Assign
		NS::pair<int, std::string> p(42, "fortytwo");
		NS::pair<int, std::string> q;
		q = p;
		std::cout << q.first << " " << q.second << std::endl;
	}
	{
		// Make_pair
		std::cout << NS::make_pair(24, "hello").first << " " << NS::make_pair(42, "world").second << std::endl;
	}
	{
		// Operators
		NS::pair<int, std::string> p(42, "fortytwo");
		NS::pair<int, std::string> q;
		std::cout << (p == q) << " " << (p != q) << std::endl;
		std::cout << (p <= q) << " " << (p >= q) << std::endl;
		std::cout << (p < q) << " " << (p > q) << std::endl;
	}
	{
		NS::pair<int, std::string> q(42, "fortytwo");
		NS::pair<int, std::string> p;
		std::cout << (p == q) << " " << (p != q) << std::endl;
		std::cout << (p <= q) << " " << (p >= q) << std::endl;
		std::cout << (p < q) << " " << (p > q) << std::endl;
	}
	{
		NS::pair<int, std::string> p(42, "fortytwo");
		NS::pair<int, std::string> q(24, "fortytwo");
		std::cout << (p == q) << " " << (p != q) << std::endl;
		std::cout << (p <= q) << " " << (p >= q) << std::endl;
		std::cout << (p < q) << " " << (p > q) << std::endl;
	}
	{
		NS::pair<int, std::string> p(42, "fortytwo");
		NS::pair<int, std::string> q(442, "fortytwo");
		std::cout << (p == q) << " " << (p != q) << std::endl;
		std::cout << (p <= q) << " " << (p >= q) << std::endl;
		std::cout << (p < q) << " " << (p > q) << std::endl;
	}
	{
		NS::pair<int, std::string> p(42, "fortytwo");
		NS::pair<int, std::string> q(42, "fortytwo");
		std::cout << (p == q) << " " << (p != q) << std::endl;
		std::cout << (p <= q) << " " << (p >= q) << std::endl;
		std::cout << (p < q) << " " << (p > q) << std::endl;
	}
	{
		NS::pair<int, std::string> p(42, "fortytwo");
		NS::pair<int, std::string> q(42, "fortytw");
		std::cout << (p == q) << " " << (p != q) << std::endl;
		std::cout << (p <= q) << " " << (p >= q) << std::endl;
		std::cout << (p < q) << " " << (p > q) << std::endl;
	}
	{
		NS::pair<int, std::string> p(42, "fortytwo");
		NS::pair<int, std::string> q(42, "luffy");
		std::cout << (p == q) << " " << (p != q) << std::endl;
		std::cout << (p <= q) << " " << (p >= q) << std::endl;
		std::cout << (p < q) << " " << (p > q) << std::endl;
	}
}

void	test_utils(void) {
	test_enable_if();
	test_is_integral();
	test_pair();
}
