#include <map>
#include <iostream>
#include "pair.hpp"
#include "AVLTree.hpp"
#include "map.hpp"

namespace ft { // namespace std would work too, but global scope would not 🤷
template <class Key, class Value>
std::ostream	&operator<<(std::ostream &os, ft::pair<Key, Value> const &p) {
	os << "(" << p.first << ", " << p.second << ")";
	return (os);
}
}

void	testAVLTree(void) {
	{
		ft::AVLTree<std::string >	tree;
		tree.insert("c");
		tree.insert("d");
		tree.insert("a");
		tree.insert("b");
		std::cout << "height: " << tree.height() << std::endl;
		std::cout << "-------------------" << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
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
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
		ft::AVLTree<int>	tree;
		tree.insert(1);
		tree.insert(-1);
		tree.insert(-4);
		tree.insert(-2);
		tree.insert(32);
		tree.insert(12);
		tree.insert(42);
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
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
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
		ft::AVLTree<ft::pair<std::string, int>, ft::map<std::string, int>::value_compare >	tree(ft::map<std::string, int>().value_comp());
		tree.insert(ft::make_pair<std::string, int>("b", 0));
		tree.insert(ft::make_pair<std::string, int>("a", 1));
		tree.insert(ft::make_pair<std::string, int>("h", -1));
		tree.insert(ft::make_pair<std::string, int>("d", 42));
		tree.insert(ft::make_pair<std::string, int>("i", 0));
		tree.insert(ft::make_pair<std::string, int>("f", -42));
		tree.insert(ft::make_pair<std::string, int>("g", 0));
		tree.insert(ft::make_pair<std::string, int>("c", 100));
		tree.insert(ft::make_pair<std::string, int>("e", 0));
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
}

void	avl_iterator_test(void) {
	{
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
		ft::AVLTree<int>::iterator	it;
		for (it = tree.begin(); it != tree.end(); it++)
			std::cout << *it << std::endl;
		std::cout << "-------------------" << std::endl;
	}
}

void	test_map(void) {
	testAVLTree();

	ft::map<std::string, int> M;
	M.insert(ft::make_pair<std::string, int>("hello", 0));
	M.insert(ft::make_pair<std::string, int>("world", -42));
	M.insert(ft::make_pair<std::string, int>("map", 42));
	M.insert(ft::make_pair<std::string, int>("vector", 42));
	M.print();

	avl_iterator_test();
}
