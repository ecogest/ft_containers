/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:26:53 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/12 14:20:57 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <ctime>
#include <fstream>

int	main(int ac, const char **av) {
	(void)ac;
	clock_t	c = clock();
	test_vector();
	test_utils();
	test_avl();
	test_map();
	test_stack();
	std::ofstream	fstream;
	fstream.open("timing", std::ios_base::app);
	fstream << av[0] << ": \e[34m" << (clock() - c) / (CLOCKS_PER_SEC / 1000.0) << "ms\e[0m elapsed" << std::endl;
	fstream.close();
	return (0);
}
