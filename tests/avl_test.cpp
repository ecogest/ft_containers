/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 10:53:13 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/11 17:26:22 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void	testAVLTree(void) {
	{ // EMPTY TREE
		std::cout << "-------------------" << std::endl;
		ft::AVLTree<std::string >	tree;
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{ // strings
		ft::AVLTree<std::string >	tree;
		tree.insert("c");
		tree.insert("d");
		tree.insert("a");
		tree.insert("b");
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{ // more strings
		ft::AVLTree<std::string>	tree;
		tree.insert("i");
		tree.insert("h");
		tree.insert("g");
		tree.insert("f");
		tree.insert("e");
		tree.insert("d");
		tree.insert("c");
		tree.insert("b");
		tree.insert("a");
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{ // numbers
		ft::AVLTree<int>	tree;
		tree.insert(1);
		tree.insert(-1);
		tree.insert(-4);
		tree.insert(-2);
		tree.insert(32);
		tree.insert(12);
		tree.insert(42);
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{ // more numbers
		ft::AVLTree<int>	tree;
		tree.insert(1000);
		tree.insert(-1000);
		tree.insert(-4000);
		tree.insert(-2000);
		tree.insert(32000);
		tree.insert(12000);
		tree.insert(42000);
		tree.insert(42);
		tree.insert(42);
		tree.insert(42);
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{ // without uniqueness (for fun)
		std::cout << "SAME, BUT WITHOUT UNIQUENESS:" << std::endl;
		ft::AVLTree<int, std::less<int>, std::allocator<int>, false>	tree;
		tree.insert(1000);
		tree.insert(-1000);
		tree.insert(-4000);
		tree.insert(-2000);
		tree.insert(32000);
		tree.insert(12000);
		tree.insert(42000);
		tree.insert(42);
		tree.insert(42);
		tree.insert(42);
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{ // with pairs
		ft::AVLTree<ft::pair<std::string, int>, ft::map<std::string, int>::value_compare >	tree(ft::map<std::string, int>().value_comp());
		tree.insert(ft::make_pair<std::string, int>("b", 0));
		tree.insert(ft::make_pair<std::string, int>("a", 1));
		tree.insert(ft::make_pair<std::string, int>("Z", 42));
		tree.insert(ft::make_pair<std::string, int>("h", -1));
		tree.insert(ft::make_pair<std::string, int>("d", 42));
		tree.insert(ft::make_pair<std::string, int>("Z", 12));
		tree.insert(ft::make_pair<std::string, int>("Z", 13));
		tree.insert(ft::make_pair<std::string, int>("i", 0));
		tree.insert(ft::make_pair<std::string, int>("f", -42));
		tree.insert(ft::make_pair<std::string, int>("g", 0));
		tree.insert(ft::make_pair<std::string, int>("c", 100));
		tree.insert(ft::make_pair<std::string, int>("e", 0));
		tree.insert(ft::make_pair<std::string, int>("Z", 23));
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{ // delete
		ft::AVLTree<std::string>	tree;
		tree.insert("i");
		tree.insert("h");
		tree.insert("g");
		tree.insert("f");
		tree.insert("e");
		tree.insert("d");
		tree.insert("c");
		tree.insert("b");
		tree.insert("a");
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
		ft::AVLTree<std::string>::iterator	it = tree.begin(); // a
		std::cout << "### Remove a:" << std::endl;
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove b:" << std::endl;
		it = tree.begin(); // b
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove c:" << std::endl;
		it = tree.begin(); // c
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove e:" << std::endl;
		it = tree.begin(); // d
		it++; // e
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove g:" << std::endl;
		it = tree.begin(); // d
		it++; // f
		it++; // g
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove h:" << std::endl;
		it = tree.begin(); // d
		it++; // f
		it++; // g
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove i:" << std::endl;
		it = tree.begin(); // d
		it++; // f
		it++; // i
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Attempt to remove END:" << std::endl;
		it = tree.begin(); // d
		it++; // f
		it++; // END
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove f:" << std::endl;
		it = tree.begin(); // d
		it++; // f
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Remove d:" << std::endl;
		it = tree.begin(); // d
		tree.erase(it);
		tree.print_2d();
		std::cout << "### Try to remove the begin of an empty tree:" << std::endl;
		it = tree.begin(); // END
		tree.erase(it);
		tree.print_2d();
	}
	{ // delete 2 (check balance)
		std::cout << "-------------------" << std::endl;
		ft::AVLTree<int>	tree;
		tree.insert(0);
		tree.insert(-1);
		tree.insert(1);
		tree.insert(2);
		tree.insert(-3);
		tree.insert(-2);
		tree.insert(2); // should not insert, it is just a check
		tree.insert(3);
		tree.insert(-4);
		// std::cout << "height: " << tree._height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
		std::cout << "Remove progressively: -4, -3, -2, -1 (to check the balance is done)" << std::endl;
		tree.erase(tree.begin()); // -4
		tree.print_2d();
		tree.erase(tree.begin()); // -3
		tree.print_2d();
		tree.erase(tree.begin()); // -2
		tree.print_2d();
		tree.erase(tree.begin()); // -1
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
}

void	avl_iterator_basic_test(void) {
	ft::AVLTree<int>	tree;
	tree.insert(1000);
	tree.insert(-1000);
	tree.insert(-4000);
	tree.insert(-2000);
	tree.insert(32000);
	tree.insert(12000);
	tree.insert(42000);
	tree.insert(42);
	tree.insert(42);
	tree.insert(42);

	std::cout << "-------------------" << std::endl;
	tree.print_2d();
	tree.print_infix();
	std::cout << "-------------------" << std::endl;
	{
		std::cout << "Increasing:" << std::endl;
		ft::AVLTree<int>::iterator	it;
		for (it = tree.begin(); it != tree.end(); it++)
			std::cout << *it << std::endl;
		std::cout << "-------------------" << std::endl;
		std::cout << "Decreasing:" << std::endl;
		it = tree.end();
		if (it != tree.begin())
			do std::cout << *--it << std::endl; while (it != tree.begin());
	}
	{
		std::cout << "Increasing:" << std::endl;
		ft::AVLTree<int>::const_iterator	it;
		for (it = tree.begin(); it != tree.end(); it++)
			std::cout << *it << std::endl;
		std::cout << "-------------------" << std::endl;
		std::cout << "Decreasing:" << std::endl;
		it = tree.end();
		if (it != tree.begin())
			do std::cout << *--it << std::endl; while (it != tree.begin());
	}
	{
		std::cout << "-------------------" << std::endl;
		std::cout << "Decreasing (reverse iterator style):" << std::endl;
		ft::AVLTree<int>::reverse_iterator	rit;
		for (rit = tree.rbegin(); rit != tree.rend(); rit++)
			std::cout << *rit << std::endl;
	}
	{
		std::cout << "-------------------" << std::endl;
		std::cout << "Decreasing (reverse iterator style):" << std::endl;
		ft::AVLTree<int>::const_reverse_iterator	rit;
		for (rit = tree.rbegin(); rit != tree.rend(); rit++)
			std::cout << *rit << std::endl;
	}
}

void	test_avl(void) {
	avl_iterator_basic_test();
	testAVLTree();
}
