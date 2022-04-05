#include <map>
#include "AVLTree.hpp"

void	testAVLTree(void) {
	{
	ft::AVLTree<std::string>	tree;
	tree.insert("c");
	tree.insert("d");
	tree.insert("a");
	tree.insert("b");
	std::cout << "-------------------" << std::endl;
	tree.print_infix();
	tree.print_2d();
	std::cout << "-------------------" << std::endl;
	}
	{
	ft::AVLTree<std::string>	tree;
	tree.insert("a");
	tree.insert("b");
	tree.insert("c");
	tree.insert("d");
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
	tree.print_infix();
	tree.print_2d();
	std::cout << "-------------------" << std::endl;
	}
}

void	test_map(void) {
	testAVLTree();
}
